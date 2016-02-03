function add_key(key)
{
  local keys = state.world2_keys;
  keys[key] = true;
  update_keys();
}

function level2_init()
{
  add_key("dashboard");  
  add_key("purple");
  add_key("green");
  add_key("red");
  add_key("blue");	
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
if(! ("world2_keys" in state))
	state.world2_keys <- {}
	
local keys = state.world2_keys;
if(! ("dashboard" in keys))
	keys.dashboard <- false;
if(! ("purple" in keys))
	keys.purple <- false;
if(! ("green" in keys))
	keys.green <- false;
if(! ("red" in keys))
	keys.red <- false;
if(! ("blue" in keys))
	keys.blue <- false;
/// this function updates the key images (call this if tux has collected a key)
function update_keys()
{
	local keys = state.world2_keys;
	key_dashboard.set_action(keys.dashboard ? "display" : "outline");
	key_purple.set_action(keys.purple ? "display" : "outline");
	key_green.set_action(keys.green ? "display" : "outline");
	key_red.set_action(keys.red ? "display" : "outline");
	key_platterblue.set_action(keys.blue ? "display" : "outline");

}

local x = 10;
local y = 2;

key_dashboard <- FloatingImage("images/objects/loot/dashboard.sprite");
key_dashboard.set_anchor_point(ANCHOR_TOP_LEFT);
key_dashboard.set_pos(x, y);
key_dashboard.set_visible(true);
x += 60;

key_purple <- FloatingImage("images/objects/loot/purple.sprite");
key_purple.set_anchor_point(ANCHOR_TOP_LEFT);
key_purple.set_pos(x, y);
key_purple.set_visible(true);
x += 60;

key_green <- FloatingImage("images/objects/loot/green.sprite");
key_green.set_anchor_point(ANCHOR_TOP_LEFT);
key_green.set_pos(x, y);
key_green.set_visible(true);
x += 60;

key_red <- FloatingImage("images/objects/loot/red.sprite");
key_red.set_anchor_point(ANCHOR_TOP_LEFT);
key_red.set_pos(x, y);
key_red.set_visible(true);
x += 60;


key_platterblue <- FloatingImage("images/objects/loot/blue.sprite");
key_platterblue.set_anchor_point(ANCHOR_TOP_LEFT);
key_platterblue.set_pos(x, y);
key_platterblue.set_visible(true);
x += 60;

update_keys();
