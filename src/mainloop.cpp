//  $Id: mainloop.cpp 5138 2007-08-15 01:02:22Z tuxdev $
//
//  SuperTux
//  Copyright (C) 2006 Matthias Braun <matze@braunis.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#include <config.h>

#include "mainloop.hpp"
#include <cstddef>

#include <stdlib.h>
#include <SDL.h>
#include "video/drawing_context.hpp"
#include "control/joystickkeyboardcontroller.hpp"
#include "gui/menu.hpp"
#include "audio/sound_manager.hpp"
#include "scripting/time_scheduler.hpp"
#include "scripting/squirrel_util.hpp"
#include "gameconfig.hpp"
#include "main.hpp"
#include "resources.hpp"
#include "screen.hpp"
#include "screen_fade.hpp"
#include "timer.hpp"
#include "player_status.hpp"
#include "random_generator.hpp"

// the engine will be run with a logical framerate of 64fps.
// We chose 64fps here because it is a power of 2, so 1/64 gives an "even"
// binary fraction...
static const float LOGICAL_FPS = 64.0;
/** ticks (as returned from SDL_GetTicks) per frame */
static const Uint32 TICKS_PER_FRAME = (Uint32) (1000.0 / LOGICAL_FPS);
/** don't skip more than every 2nd frame */
static const int MAX_FRAME_SKIP = 2;

MainLoop* main_loop = NULL;

MainLoop::MainLoop()
  : speed(1.0), nextpop(false), nextpush(false), fps(0), screenshot_requested(false)
{
  using namespace Scripting;
  TimeScheduler::instance = new TimeScheduler();
}

MainLoop::~MainLoop()
{
  using namespace Scripting;
  delete TimeScheduler::instance;
  TimeScheduler::instance = NULL;

  for(std::vector<Screen*>::iterator i = screen_stack.begin();
      i != screen_stack.end(); ++i) {
    delete *i;
  }
}

void
MainLoop::push_screen(Screen* screen, ScreenFade* screen_fade)
{
  this->next_screen.reset(screen);
  this->screen_fade.reset(screen_fade);
  nextpush = !nextpop;
  nextpop = false;
  speed = 1.0;
}

void
MainLoop::exit_screen(ScreenFade* screen_fade)
{
  next_screen.reset(NULL);
  this->screen_fade.reset(screen_fade);
  nextpop = true;
  nextpush = false;
}

void
MainLoop::set_screen_fade(ScreenFade* screen_fade)
{
  this->screen_fade.reset(screen_fade);
}

void
MainLoop::quit(ScreenFade* screen_fade)
{
  for(std::vector<Screen*>::iterator i = screen_stack.begin();
          i != screen_stack.end(); ++i)
    delete *i;
  screen_stack.clear();

  exit_screen(screen_fade);
}

void
MainLoop::set_speed(float speed)
{
  this->speed = speed;
}

float
MainLoop::get_speed() const
{
  return speed;
}

void
MainLoop::draw_fps(DrawingContext& context, float fps_fps)
{
  char str[60];
  snprintf(str, sizeof(str), "%3.1f", fps_fps);
  const char* fpstext = "FPS";
  context.draw_text(white_text, fpstext, Vector(SCREEN_WIDTH - white_text->get_text_width(fpstext) - gold_text->get_text_width(" 99999") - BORDER_X, BORDER_Y + 20), ALIGN_LEFT, LAYER_HUD);
  context.draw_text(gold_text, str, Vector(SCREEN_WIDTH - BORDER_X, BORDER_Y + 20), ALIGN_RIGHT, LAYER_HUD);
}

void
MainLoop::draw(DrawingContext& context)
{
  static Uint32 fps_ticks = SDL_GetTicks();
  static int frame_count = 0;

  current_screen->draw(context);
  if(Menu::current() != NULL)
    Menu::current()->draw(context);
  if(screen_fade.get() != NULL)
    screen_fade->draw(context);
  Console::instance->draw(context);

  if(config->show_fps)
    draw_fps(context, fps);

  // if a screenshot was requested, pass request on to drawing_context
  if (screenshot_requested) {
    context.take_screenshot();
    screenshot_requested = false;
  }
  context.do_drawing();

  /* Calculate frames per second */
  if(config->show_fps)
  {
    ++frame_count;

    if(SDL_GetTicks() - fps_ticks >= 500)
    {
      fps = (float) frame_count / .5;
      frame_count = 0;
      fps_ticks = SDL_GetTicks();
    }
  }
}

void
MainLoop::update_gamelogic(float elapsed_time)
{
  Scripting::update_debugger();
  Scripting::TimeScheduler::instance->update(game_time);
  current_screen->update(elapsed_time);
  if(screen_fade.get() != NULL)
    screen_fade->update(elapsed_time);
  Console::instance->update(elapsed_time);
}

void
MainLoop::process_events()
{
  main_controller->update();
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    main_controller->process_event(event);
    if(Menu::current() != NULL)
      Menu::current()->event(event);
    if(event.type == SDL_QUIT)
      quit();
    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F11) {
      config->use_fullscreen = !config->use_fullscreen;
      init_video();
    }
    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_PRINT) {
      take_screenshot();
    }
  }
}

void
MainLoop::handle_screen_switch()
{
  while( (next_screen.get() != NULL || nextpop) &&
      (screen_fade.get() == NULL || screen_fade->done())) {
    if(current_screen.get() != NULL) {
      current_screen->leave();
    }

    if(nextpop) {
      if(screen_stack.empty()) {
        running = false;
        break;
      }
      next_screen.reset(screen_stack.back());
      screen_stack.pop_back();
    }
    if(nextpush && current_screen.get() != NULL) {
      screen_stack.push_back(current_screen.release());
    }

    nextpush = false;
    nextpop = false;
    speed = 1.0;
    if(next_screen.get() != NULL)
      next_screen->setup();
    current_screen.reset(next_screen.release());
    screen_fade.reset(NULL);

    waiting_threads.wakeup();
  }
}

void
MainLoop::run(DrawingContext &context)
{
  Uint32 last_ticks = 0;
  Uint32 elapsed_ticks = 0;

  running = true;
  while(running) {

    handle_screen_switch();
    if(!running || current_screen.get() == NULL)
      break;

    Uint32 ticks = SDL_GetTicks();
    elapsed_ticks += ticks - last_ticks;
    last_ticks = ticks;

    if (elapsed_ticks > TICKS_PER_FRAME*4) {
      // when the game loads up or levels are switched the
      // elapsed_ticks grows extremly large, so we just ignore those
      // large time jumps
      elapsed_ticks = 0;
    }

    int frames = 0;

    if (elapsed_ticks > TICKS_PER_FRAME) {
      while(elapsed_ticks > TICKS_PER_FRAME && frames < MAX_FRAME_SKIP) {
        elapsed_ticks -= TICKS_PER_FRAME;
        float timestep = 1.0 / LOGICAL_FPS;
        real_time += timestep;
        timestep *= speed;
        game_time += timestep;

        process_events();
        update_gamelogic(timestep);
        frames += 1;
      }

      draw(context);
    }

    sound_manager->update();

    SDL_Delay(0);
  }
}

void 
MainLoop::take_screenshot()
{
  screenshot_requested = true;
}

