//  $Id: particlesystem.hpp 4059 2006-07-21 11:45:14Z matzebraun $
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

#ifndef TUXJUNIOR_PARTICLESYSTEM_H
#define TUXJUNIOR_PARTICLESYSTEM_H

#include <vector>

#include "video/surface.hpp"
#include "game_object.hpp"
#include "serializable.hpp"
#include "sector.hpp"
#include "math/vector.hpp"

namespace lisp {
class Lisp;
}

class DisplayManager;

/**
 * This is the base class for particle systems. It is responsible for storing a
 * set of particles with each having an x- and y-coordinate the number of the
 * layer where it should be drawn and a texture.
 * The coordinate system used here is a virtual one. It would be a bad idea to
 * populate whole levels with particles. So we're using a virtual rectangle
 * here that is tiled onto the level when drawing. This rect.has the size
 * (virtual_width, virtual_height). We're using modulo on the particle
 * coordinates, so when a particle leaves left, it'll reenter at the right
 * side.
 *
 * Classes that implement a particle system should subclass from this class,
 * initialize particles in the constructor and move them in the simulate
 * function.
 */
class ParticleSystem : public GameObject
{
public:
    ParticleSystem(float max_particle_size = 60);
    virtual ~ParticleSystem();

    virtual void draw(DrawingContext& context);

protected:
    float max_particle_size;
    int z_pos;

    class Particle
    {
    public:
        virtual ~Particle()
        { }

        Vector pos;
        Surface* texture;
    };

    std::vector<Particle*> particles;
    float virtual_width, virtual_height;
};

class SnowParticleSystem : public ParticleSystem, public Serializable
{
public:
    SnowParticleSystem();
    virtual ~SnowParticleSystem();

    void parse(const lisp::Lisp& lisp);
    void write(lisp::Writer& writer);

    virtual void update(float elapsed_time);

    std::string type() const
    { return "SnowParticleSystem"; }

private:
    class SnowParticle : public Particle
    {
    public:
        float speed;
	float wobble;
	float anchorx;
	float drift_speed;
    };

    Surface* snowimages[3];
};

class GhostParticleSystem : public ParticleSystem, public Serializable
{
public:
    GhostParticleSystem();
    virtual ~GhostParticleSystem();

    void parse(const lisp::Lisp& lisp);
    void write(lisp::Writer& writer);

    virtual void update(float elapsed_time);

    std::string type() const
    { return "GhostParticleSystem"; }

private:
    class GhostParticle : public Particle
    {
    public:
        float speed;
    };

    Surface* ghosts[2];
};

class CloudParticleSystem : public ParticleSystem, public Serializable
{
public:
    CloudParticleSystem();
    virtual ~CloudParticleSystem();

    void parse(const lisp::Lisp& lisp);
    void write(lisp::Writer& writer);

    virtual void update(float elapsed_time);

    std::string type() const
    { return "CloudParticleSystem"; }

private:
    class CloudParticle : public Particle
    {
    public:
        float speed;
    };

    Surface* cloudimage;
};

#endif
