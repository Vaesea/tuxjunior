function add_key(key)
{
  local keys = state.world1_keys;
  keys[key] = true;
  update_keys();
}

function level2_init()
{
 
  add_key("red");
  add_key("purple")
  add_key("blue");
  add_key("green");
  add_key("yellow");	
  add_key("orange")
  Tux.deactivate();
  Effect.sixteen_to_nine(2);
  Text.set_text(translate("---Insert Cutscene Here---"));
  Tux.walk(100);
  Text.fade_in(2);
  wait(4);
  Text.fade_out(1);
  wait(1);
  Effect.four_to_three();
  Tux.activate();
}

/***************************************
 * Handling of the "keys" in the world *
 ***************************************/
if(! ("world1_keys" in state))
	state.world1_keys <- {}
local keys = state.world1_keys;
if(! ("dashboard" in keys))
	keys.dashboard <- false;
if(! ("red" in keys))
	keys.red <- false;
if(! ("purple" in keys))
	keys.purple <- false;
if(! ("blue" in keys))
	keys.blue <- false;
if(! ("green" in keys))
	keys.green <- false;
if(! ("yellow" in keys))
	keys.yellow <- false;
if(! ("orange" in keys))
	keys.orange <- false;
/// this function updates the key images (call this if tux has collected a key)
function update_keys()
{

	local keys = state.world1_keys;
	key_dashboard.set_action(keys.dashboard ? "display" : "outline");

	key_blue.set_action(keys.blue ? "display" : "outline");
	key_green.set_action(keys.green ? "display" : "outline");
	key_yellow.set_action(keys.yellow ? "display" : "outline");
	key_orange.set_action(keys.orange ? "display" : "outline");
	key_red.set_action(keys.red ? "display" : "outline");
	key_purple.set_action(keys.purple ? "display" : "outline");
	key_blue.set_action(keys.blue ? "display" : "outline");

}

local x = 0;
local y = 0;

key_dashboard <- FloatingImage("images/objects/loot/dashboard.sprite");
key_dashboard.set_anchor_point(ANCHOR_BOTTOM_LEFT);
key_dashboard.set_pos(x, y);
key_dashboard.set_visible(true);


key_green <- FloatingImage("images/objects/loot/green.sprite");
key_green.set_anchor_point(ANCHOR_BOTTOM_RIGHT);
key_green.set_pos(x, y);
key_green.set_visible(true);
x -= 42;


key_orange <- FloatingImage("images/objects/loot/orange.sprite");
key_orange.set_anchor_point(ANCHOR_BOTTOM_RIGHT);
key_orange.set_pos(x, y);
key_orange.set_visible(true);
x -=36;

key_red <- FloatingImage("images/objects/loot/red.sprite");
key_red.set_anchor_point(ANCHOR_BOTTOM_RIGHT);
key_red.set_pos(x, y);
key_red.set_visible(true);
x -= 42;


key_yellow <- FloatingImage("images/objects/loot/yellow.sprite");
key_yellow.set_anchor_point(ANCHOR_BOTTOM_RIGHT);
key_yellow.set_pos(x, y);
key_yellow.set_visible(true);
x -= 42;


key_purple <- FloatingImage("images/objects/loot/purple.sprite");
key_purple.set_anchor_point(ANCHOR_BOTTOM_RIGHT);
key_purple.set_pos(x, y);
key_purple.set_visible(true);
x -= 42;


key_blue <- FloatingImage("images/objects/loot/blue.sprite");
key_blue.set_anchor_point(ANCHOR_BOTTOM_RIGHT);
key_blue.set_pos(x, y);
key_blue.set_visible(true);
x -= 42;

update_keys();
