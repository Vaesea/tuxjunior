//  $Id: Objects.cs 5761 2008-08-31 19:32:56Z mmlosh $
using Sprites;
using System;
using LispReader;
using DataStructures;
using System.Collections.Generic;
using SceneGraph;
using OpenGl;

/// <summary>
/// Used to make it simpler to change common tooltip strings.
/// </summary>
internal static class ToolTipStrings {
	/// <summary>
	/// For the "Name" attribute used for scripting.
	/// </summary>
	internal const string ScriptingName = "Used to refer to the object from a script. If it isn't set the object can't be scripted.";
}


// TODO: Write better documentation.
/// <summary>Attribute that marks a class as an object for use in levels/worldmaps.</summary>
[AttributeUsage(AttributeTargets.Class, AllowMultiple=false)]
public sealed class TuxjuniorObjectAttribute : Attribute
{
	/// <summary>Tells when the object will be shown in the object list.</summary>
	public enum Usage {
		/// <summary>Should only be shown everywhere. This is the default.</summary>
		Any,
		/// <summary>Should not be shown at all.</summary>
		None,
		/// <summary>Should only be shown for worldmaps.</summary>
		WorldmapOnly,
		/// <summary>Should only be shown for "normal" levels.</summary>
		LevelOnly
	}

	public string Name;
	public string IconSprite;
	public string ObjectListAction;
	/// <summary>A <see cref="Usage"/> enum describing where the object can be used.</summary>
	public Usage Target;

	/// <summary>Constructs for <see cref="TuxjuniorObjectAttribute"/>.</summary>
	/// <param name="Name">Name of object in the level file</param>
	/// <param name="IconSprite">Icon used in the object list in the editor</param>
	public TuxjuniorObjectAttribute(string Name, string IconSprite) {
		this.Name = Name;
		this.IconSprite = IconSprite;
	}
}

#region Badguys

[TuxjuniorObject("mrbomb", "images/creatures/mr_bomb/mr_bomb.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class MrBomb : SimpleDirObject
{
	[ChooseResourceSetting]
	[LispChild("sprite", Optional = true, Default = "")]
	public string SpriteFile {
		get {
			return spriteFile;
		}
		set {
			if (!String.IsNullOrEmpty(value)){
				//TODO: find out why cherry's sprite causes problems. Particles?
				Sprite newSprite= SpriteManager.Create(value);
				newSprite.Action = "left";
				Sprite = newSprite;	//save new sprite after (no exception only)
			}
			spriteFile = value;
		}
	}
	private string spriteFile = String.Empty;
	public MrBomb() {
		Sprite = SpriteManager.Create("images/creatures/mr_bomb/mr_bomb.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("snowball", "images/creatures/snowball/snowball.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Snowball : SimpleDirObject
{
	public Snowball() {
		Sprite = SpriteManager.Create("images/creatures/snowball/snowball.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("smartball", "images/creatures/snowball/smart-snowball.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class SmartBall : SimpleDirObject
{
	public SmartBall() {
		Sprite = SpriteManager.Create("images/creatures/snowball/smart-snowball.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("captainsnowball", "images/creatures/snowball/cpt-snowball.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class CaptainSnowball : SimpleDirObject
{
	public CaptainSnowball() {
		Sprite = SpriteManager.Create("images/creatures/snowball/cpt-snowball.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("kamikazesnowball", "images/creatures/snowball/kamikaze-snowball.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class KamikazeSnowball : SimpleDirObject
{
	public KamikazeSnowball() {
		Sprite = SpriteManager.Create("images/creatures/snowball/kamikaze-snowball.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("crystallo", "images/creatures/crystallo/crystallo.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Crystallo : SimpleDirObject
{
	[LispChild("radius", Optional = true, Default = 100f)]
	public float Radius = 100f;
	
	public Crystallo() {
		Sprite = SpriteManager.Create("images/creatures/crystallo/crystallo.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("stalactite", "images/creatures/stalactite/stalactite.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Stalactite : SimpleObject
{
	public Stalactite() {
		Sprite = SpriteManager.Create("images/creatures/stalactite/stalactite.sprite");
		Sprite.Action = "normal";
	}
}

[TuxjuniorObject("mriceblock", "images/creatures/mr_iceblock/mr_iceblock.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class MrIceBlock : SimpleDirObject
{
	public MrIceBlock() {
		Sprite = SpriteManager.Create("images/creatures/mr_iceblock/mr_iceblock.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("bouncingsnowball",
                "images/creatures/bouncing_snowball/bouncing_snowball.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class BouncingSnowball : SimpleDirObject
{
	public BouncingSnowball() {
		Sprite = SpriteManager.Create("images/creatures/bouncing_snowball/bouncing_snowball.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("flyingsnowball",
                "images/creatures/flying_snowball/flying_snowball.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class FlyingSnowball : SimpleObject
{
	public FlyingSnowball() {
		Sprite = SpriteManager.Create("images/creatures/flying_snowball/flying_snowball.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("jumpy", "images/creatures/jumpy/jumpy.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "left-up")]
public sealed class Jumpy : SimpleObject
{
	public Jumpy() {
		Sprite = SpriteManager.Create("images/creatures/jumpy/jumpy.sprite");
		Sprite.Action = "left-up";
	}
}

[TuxjuniorObject("spiky", "images/creatures/spiky/spiky.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Spiky : SimpleDirObject
{
	public Spiky() {
		Sprite = SpriteManager.Create("images/creatures/spiky/spiky.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("sspiky", "images/creatures/spiky/sleepingspiky.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "sleeping-left")]
public sealed class SleepSpiky : SimpleDirObject
{
	protected override void DirectionChanged() {
		Sprite.Action = (Direction == Directions.right) ? "sleeping-right" : "sleeping-left";
	}

	public SleepSpiky() {
		Sprite = SpriteManager.Create("images/creatures/spiky/sleepingspiky.sprite");
		Sprite.Action = "sleeping-left";
	}
}

[TuxjuniorObject("flame", "images/creatures/flame/flame.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Flame : SimpleObject
{
	[LispChild("radius", Optional = true, Default = 100f)]
	public float Radius = 100f;
	[LispChild("speed", Optional = true, Default = 2f)]
	public float Speed = 2;

	public Flame() {
		Sprite = SpriteManager.Create("images/creatures/flame/flame.sprite");
		Sprite.Action = "normal";
	}
}

[TuxjuniorObject("fish", "images/creatures/fish/fish.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Fish : SimpleObject
{
	public Fish() {
		Sprite = SpriteManager.Create("images/creatures/fish/fish.sprite");
		Sprite.Action = "normal";
	}
}

[TuxjuniorObject("mrtree", "images/creatures/mr_tree/mr_tree.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class MrTree : SimpleDirObject
{
	public MrTree() {
		Sprite = SpriteManager.Create("images/creatures/mr_tree/mr_tree.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("stumpy", "images/creatures/mr_tree/stumpy.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Stumpy : SimpleDirObject
{
	public Stumpy() {
		Sprite = SpriteManager.Create("images/creatures/mr_tree/stumpy.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("poisonivy", "images/creatures/poison_ivy/poison_ivy.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class PoisonIvy : SimpleDirObject
{
	public PoisonIvy() {
		Sprite = SpriteManager.Create("images/creatures/poison_ivy/poison_ivy.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("walkingleaf", "images/creatures/walkingleaf/walkingleaf.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class WalkingLeaf : SimpleDirObject
{
	public WalkingLeaf() {
		Sprite = SpriteManager.Create("images/creatures/walkingleaf/walkingleaf.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("zeekling", "images/creatures/zeekling/zeekling.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Zeekling : SimpleDirObject
{
	public Zeekling() {
		Sprite = SpriteManager.Create("images/creatures/zeekling/zeekling.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("mrrocket", "images/creatures/mr_rocket/mr_rocket.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class MrRocket : SimpleDirObject
{
	public MrRocket() {
		Sprite = SpriteManager.Create("images/creatures/mr_rocket/mr_rocket.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("snail", "images/creatures/snail/snail.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Snail : SimpleDirObject
{
	public Snail() {
		Sprite = SpriteManager.Create("images/creatures/snail/snail.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("totem", "images/creatures/totem/totem.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "walking-left")]
public sealed class Totem : SimpleObject
{
	public Totem() {
		Sprite = SpriteManager.Create("images/creatures/totem/totem.sprite");
		Sprite.Action = "walking-left";
	}
}

[TuxjuniorObject("kugelblitz", "images/creatures/kugelblitz/kugelblitz.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "falling")]
public sealed class Kugelblitz : SimpleObject
{
	public Kugelblitz() {
		Sprite = SpriteManager.Create("images/creatures/kugelblitz/kugelblitz.sprite");
		Sprite.Action = "falling";
	}
}

[TuxjuniorObject("dispenser", "images/creatures/dispenser/dispenser.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "dropper")]
public sealed class Dispenser : SimpleDirObject
{
	private bool random;

	[PropertyProperties(Tooltip = "Put a tick here to make badguys order random")]
	[LispChild("random", Optional = true, Default = false)]
	public bool Random {
		get {
			return random;
		}
		set {
			random = value;
		}
	}


	/// <summary>
	/// Type of dispenser.
	/// </summary>
	public enum DispenserTypes {
		rocketlauncher,
		cannon,
		dropper
	}

	private DispenserTypes dispenserType = DispenserTypes.dropper;
	private List<string> badguy = new List<string>();

	[PropertyProperties(Tooltip = "Type of dispenser to shoot from.")]
	[LispChild("type", Optional = true, Default = DispenserTypes.dropper)]
	public DispenserTypes DispenserType {
		get {
			return dispenserType;
		}
		set {
			dispenserType = value;
			if (value == DispenserTypes.rocketlauncher)
				Sprite.Action = (Direction == Directions.right) ? "working-right" : "working-left";
			else if (value == DispenserTypes.cannon)
				Sprite.Action = "working";
			else
				Sprite.Action = "dropper";
		}
	}

	[ChooseBadguySetting]
	[PropertyProperties(Tooltip = "Badguys which will dispenser shoot. To add badguy just drag it here from badguy list.")]
	[LispChild("badguy")]
	public List<string> Badguy {
		get {
			return badguy;
		}
		set {
			badguy = value;
		}
	}

	protected override void DirectionChanged() {
		if (dispenserType == DispenserTypes.rocketlauncher) {
			Sprite.Action = (Direction == Directions.right) ? "working-right" : "working-left";
		}
	}

	[LispChild("cycle")]
	public float Cycle = 1;

	public Dispenser() {
		Sprite = SpriteManager.Create("images/creatures/dispenser/dispenser.sprite");
		Sprite.Action = "dropper";
		badguy.Add("snowball");
	}

	public override object Clone() {
		Dispenser aClone = (Dispenser) MemberwiseClone();
		aClone.badguy = new List<string>(aClone.badguy);
		return aClone;
	}
}

[TuxjuniorObject("angrystone", "images/creatures/angrystone/angrystone.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "idle")]
public sealed class AngryStone : SimpleObject
{
	public AngryStone() {
		Sprite = SpriteManager.Create("images/creatures/angrystone/angrystone.sprite");
		Sprite.Action = "idle";
	}
}

[TuxjuniorObject("icecrusher", "images/creatures/icecrusher/icecrusher.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "idle")]
public sealed class IceCrusher : SimpleObject
{
	public IceCrusher() {
		Sprite = SpriteManager.Create("images/creatures/icecrusher/icecrusher.sprite");
		Sprite.Action = "idle";
	}
}


[TuxjuniorObject("spidermite", "images/creatures/spidermite/spidermite.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Spidermite : SimpleObject
{
	public Spidermite() {
		Sprite = SpriteManager.Create("images/creatures/spidermite/spidermite.sprite");
		Sprite.Action = "left";
	}
}

[TuxjuniorObject("plant", "images/creatures/plant/plant.sprite",
                Target = TuxjuniorObjectAttribute.Usage.None)]
public sealed class Plant : SimpleObject
{
	public Plant() {
		Sprite = SpriteManager.Create("images/creatures/plant/plant.sprite");
	}
}

[TuxjuniorObject("nolok_01", "images/creatures/nolok/nolok.sprite",
                Target = TuxjuniorObjectAttribute.Usage.None)]
public sealed class Nolok_01 : SimpleObject
{
	public Nolok_01() {
		Sprite = SpriteManager.Create("images/creatures/nolok/nolok.sprite");
	}
}

[TuxjuniorObject("willowisp",
                "images/creatures/willowisp/willowisp.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "idle")]
public sealed class WilloWisp : SimpleObject, IPathObject
{
	[LispChild("sector"), ChooseSectorSetting()]
	public string Sector = String.Empty;
	[LispChild("spawnpoint")]
	public string SpawnPoint = String.Empty;
	[LispChild("name")]
	public string Name;
	[LispChild("flyspeed", Optional = true, Default=64f)]
	public float FlySpeed = 64f;
	[LispChild("track-range", Optional = true, Default=384f)]
	public float TrackRange = 384f;
	[LispChild("vanish-range", Optional = true, Default=512f)]
	public float VanishRange = 512f;
	[LispChild("hit-script", Optional = true, Default = "")]
	[EditScriptSetting]
	public string HitScript;

	private Path path = new Path();
	[LispChild("path", Optional = true, Default = null)]
	public Path Path {
		get {
			return path;
		}
		set {
			path = value;
		}
	}

	public WilloWisp() {
		Sprite = SpriteManager.Create("images/creatures/willowisp/willowisp.sprite");
		Sprite.Action = "idle";
	}
}

[TuxjuniorObject("darttrap", "images/creatures/darttrap/darttrap.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "idle-left")]
public sealed class DartTrap : SimpleDirObject
{
	[LispChild("initial-delay")]
	public float initial_delay = 0;
	[LispChild("fire-delay")]
	public float fire_delay = 2;
	[LispChild("ammo")]
	public int ammo = -1;

	protected override void DirectionChanged() {
		Sprite.Action = (Direction == Directions.right) ? "idle-right" : "idle-left";
	}

	public DartTrap() {
		Sprite = SpriteManager.Create("images/creatures/darttrap/darttrap.sprite");
		Sprite.Action = "idle-left";
	}
}

[TuxjuniorObject("skullyhop", "images/creatures/skullyhop/skullyhop.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "standing-left")]
public sealed class SkullyHop : SimpleDirObject
{
	protected override void DirectionChanged() {
		Sprite.Action = (Direction == Directions.right) ? "standing-right" : "standing-left";
	}

	public SkullyHop() {
		Sprite = SpriteManager.Create("images/creatures/skullyhop/skullyhop.sprite");
		Sprite.Action = "standing-left";
	}
}

[TuxjuniorObject("igel", "images/creatures/igel/igel.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "walking-left")]
public sealed class Igel : SimpleDirObject
{
	public Igel() {
		Sprite = SpriteManager.Create("images/creatures/igel/igel.sprite");
		Sprite.Action = "walking-left";
	}
}

[TuxjuniorObject("toad", "images/creatures/toad/toad.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction ="idle-left")]
public sealed class Toad : SimpleDirObject
{
	protected override void DirectionChanged() {
		Sprite.Action = (Direction == Directions.right) ? "idle-right" : "idle-left";
	}

	public Toad() {
		Sprite = SpriteManager.Create("images/creatures/toad/toad.sprite");
		Sprite.Action = "idle-left";
	}
}

[TuxjuniorObject("mole", "images/creatures/mole/mole.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "idle")]
public sealed class Mole : SimpleObject
{
	public Mole() {
		Sprite = SpriteManager.Create("images/creatures/mole/mole.sprite");
		Sprite.Action = "idle";
	}
}

#region Bosses
[TuxjuniorObject("yeti", "images/creatures/yeti/yeti.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "stand-left")]
public sealed class Yeti : SimpleObject
{

	[LispChild("dead-script", Optional = true, Default = "")]
	[EditScriptSetting]
	public String DeadScript = String.Empty;

	public Yeti() {
		Sprite = SpriteManager.Create("images/creatures/yeti/yeti.sprite");
		Sprite.Action = "stand-left";
	}
}

[TuxjuniorObject("yeti_stalactite", "images/engine/editor/stalactite_yeti.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class StalactiteYeti : SimpleObject
{
	public StalactiteYeti() {
		Sprite = SpriteManager.Create("images/creatures/stalactite/stalactite.sprite");
		Sprite.Action = "normal";
	}
}

[TuxjuniorObject("ghosttree", "images/creatures/ghosttree/ghosttree.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "default")]
public sealed class GhostTree : SimpleObject
{
	public GhostTree() {
		Sprite = SpriteManager.Create("images/creatures/ghosttree/ghosttree.sprite");
		Sprite.Action = "default";
	}
}

#endregion Bosses

#endregion Badguys

#region SpawnAndDoors
[TuxjuniorObject("spawnpoint", "images/engine/editor/spawnpoint.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class SpawnPoint : SimpleObject {
	[LispChild("name")]
	public string Name;

	public SpawnPoint() {
		Sprite = SpriteManager.CreateFromImage("images/engine/editor/spawnpoint.png");
		Sprite.Action = "default";
	}
}

[TuxjuniorObject("firefly", "images/engine/editor/resetpoint.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Firefly : SimpleObject
{
	[ChooseResourceSetting]
	[LispChild("sprite", Optional = true, Default = "")]
	public string SpriteFile {
		get {
			return spriteFile;
		}
		set {
			if(!String.IsNullOrEmpty(value))
				Sprite = SpriteManager.Create(value);
			spriteFile = value;
		}
	}
	private string spriteFile = String.Empty;
	public Firefly() {
		Sprite = SpriteManager.Create("images/objects/resetpoints/default-resetpoint.sprite");
		Sprite.Action = "normal";
	}
}

[TuxjuniorObject("door", "images/objects/door/door.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "closed")]
public sealed class Door : SimpleObject
{
	[LispChild("sector"), ChooseSectorSetting()]
	public string Sector;
	[LispChild("spawnpoint")]
	public string Spawnpoint;

	public Door() {
		Sprite = SpriteManager.Create("images/objects/door/door.sprite");
		Sprite.Action = "closed";
	}
}
#endregion SpawnAndDoors

#region Light

[TuxjuniorObject("spotlight", "images/objects/spotlight/spotlight_base.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Spotlight : SimpleColorObject
{
	[LispChild("angle")]
	public float Angle;

	[ChooseColorSetting(UseAlpha = true)]
	[LispChild("color", Optional = true )]
	public Drawing.Color color = new Drawing.Color( 1f, 1f, 1f );

	public Spotlight() {
		Sprite = SpriteManager.Create("images/objects/spotlight/spotlight_base.sprite");
		Sprite.Action = "default";
	}
	public override void Draw(Gdk.Rectangle cliprect) {
		if (!cliprect.IntersectsWith((Gdk.Rectangle) Area))
			return;
		// Draw sprite
		if(Sprite == null)
			return;

		Sprite.Draw(new Vector(X, Y));
		// Draw a color rectangle
		DrawColor(color);
	}
}

[TuxjuniorObject("magicblock", "images/objects/magicblock/magicblock.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class MagicBlock : SimpleColorObject
{
	[ChooseColorSetting]
	[LispChild("color")]
	public Drawing.Color MagicColor {
		get {
			return magiccolor;
		}
		set { //Limit color to 8 useful values (white red green blue yellow violet cyan black)
			magiccolor.Red = (value.Red >= 0.5f?1f:0);
			magiccolor.Green = (value.Green >= 0.5f?1f:0);
			magiccolor.Blue = (value.Blue >= 0.5f?1f:0);
		}
	}
	private Drawing.Color magiccolor = new Drawing.Color( 1f, 0f, 0f );

	public override void Draw(Gdk.Rectangle cliprect) {
		if (!cliprect.IntersectsWith((Gdk.Rectangle) Area))
			return;
		// Draw sprite
		if(Sprite == null)
			return;

		Sprite.Draw(new Vector(X, Y));
		// Draw a color rectangle
		DrawColor(magiccolor);
	}
	public MagicBlock() {
		Sprite = SpriteManager.Create("images/objects/magicblock/magicblock.sprite");
		Sprite.Action = "normal";
	}
}

[TuxjuniorObject("lantern", "images/objects/lantern/lantern.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Lantern : SimpleColorObject
{
	[ChooseColorSetting]
	[LispChild("color")]
	public Drawing.Color LightColor {
		get {
			return lightcolor;
		}
		set { ////Limit color to 8 useful values (white red green blue yellow violet cyan black)
			lightcolor.Red = (value.Red >= 0.5f?1f:0);
			lightcolor.Green = (value.Green >= 0.5f?1f:0);
			lightcolor.Blue = (value.Blue >= 0.5f?1f:0);
		}
	}
	private Drawing.Color lightcolor = new Drawing.Color( 1f, 1f, 1f );

	public override void Draw(Gdk.Rectangle cliprect) {
		if (!cliprect.IntersectsWith((Gdk.Rectangle) Area))
			return;
		// Draw sprite
		if(Sprite == null)
			return;

		Sprite.Draw(new Vector(X, Y));
		// Draw a color rectangle
		DrawColor(lightcolor);
	}
	public Lantern() {
		Sprite = SpriteManager.Create("images/objects/lantern/lantern.sprite");
		Sprite.Action = "normal";
	}
}

[TuxjuniorObject("candle", "images/objects/candle/candle.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "on")]
public sealed class Candle : SimpleObject
{
	[PropertyProperties(Tooltip = ToolTipStrings.ScriptingName)]
	[LispChild("name", Optional = true, Default = "")]
	public string Name = String.Empty;
	[PropertyProperties(Tooltip = "If enabled the candle will be burning initially.")]
	[LispChild("burning", Optional = true, Default = true)]
	public bool Burning = true;

	public Candle() {
		Sprite = SpriteManager.Create("images/objects/candle/candle.sprite");
		Sprite.Action = "on";
	}
}

#endregion Light

#region Switches

[TuxjuniorObject("switch", "images/objects/switch/switch-0.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Switch : SimpleObject
{
	[ChooseResourceSetting]
	[LispChild("sprite")]
	public string SpriteFile {
		get {
			return spriteFile;
		}
		set {
			if (!String.IsNullOrEmpty(value)) {
				Sprite newSprite = SpriteManager.Create(value);
				newSprite.Action = "off";
				Sprite = newSprite;	//save new sprite after (no exception only)
			}
			spriteFile = value;
		}
	}
	private string spriteFile = "images/objects/switch/switch.sprite";

	[LispChild("script")]
	[EditScriptSetting]
	public string Script = String.Empty;

	public Switch() {
		Sprite = SpriteManager.Create("images/objects/switch/switch.sprite");
		Sprite.Action = "off";
	}
}

[TuxjuniorObject("pushbutton", "images/objects/pushbutton/pushbutton.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "off")]
public sealed class PushButton : SimpleObject
{
	[LispChild("script")]
	[EditScriptSetting]
	public string Script = String.Empty;

	public PushButton() {
		Sprite = SpriteManager.Create("images/objects/pushbutton/pushbutton.sprite");
		Sprite.Action = "off";
	}
}

[TuxjuniorObject("ispy", "images/objects/ispy/ispy.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly,
                ObjectListAction = "idle-left")]
public sealed class Ispy : SimpleDirObject
{
	[LispChild("script")]
	[EditScriptSetting]
	public string Script = String.Empty;

	[LispChild("facing-down", Optional = true, Default = false)]
	public bool FacingDown {
		get {
			return facingDown;
		}
		set {
			facingDown = value;
			this.DirectionChanged();
		}
	}

	private bool facingDown;

	protected override void DirectionChanged() {
		if (facingDown) {
			Sprite.Action = "idle-down";
		} else {
			Sprite.Action = (Direction == Directions.left) ? "idle-left" : "idle-right";
		}
	}

	public Ispy() {
		Sprite = SpriteManager.Create("images/objects/ispy/ispy.sprite");
		Sprite.Action = "idle-right";
	}
}

#endregion Switches

#region Portables
[TuxjuniorObject("trampoline", "images/objects/trampoline/trampoline.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Trampoline : SimpleObject
{
	[PropertyProperties(Tooltip = "If enabled Tux can carry the trampoline around.")]
	[LispChild("portable", Optional = true, Default = true)]
	public bool Portable {
		get {
			return portable;
		}
		set {
			portable = value;
			if( value == false ){
				Sprite = SpriteManager.Create("images/objects/trampoline/trampoline_fix.sprite");
			} else {
				Sprite = SpriteManager.Create("images/objects/trampoline/trampoline.sprite");
			}
			Sprite.Action = "normal";
		}
	}
	private bool portable = true;
	public Trampoline() {
		Sprite = SpriteManager.Create("images/objects/trampoline/trampoline.sprite");
		Sprite.Action = "normal";
	}
}

[TuxjuniorObject("rock", "images/objects/rock/rock.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Rock : SimpleObject
{
	public Rock() {
		Sprite = SpriteManager.Create("images/objects/rock/rock.sprite");
		Sprite.Action = "normal";
	}
}

#endregion Portables

#region Platforms

[TuxjuniorObject("platform",
                "images/objects/flying_platform/flying_platform.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class FlyingPlatform : SimplePathObject
{
	public FlyingPlatform()
	{
		SpriteFile = "images/objects/flying_platform/flying_platform.sprite";
	}
}

[TuxjuniorObject("hurting_platform",
                "images/objects/sawblade/sawblade.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class HurtingPlatform : SimplePathObject
{
	public HurtingPlatform()
	{
		SpriteFile = "images/objects/sawblade/sawblade.sprite";
	}
}

#endregion Platforms

#region TileLike

[TuxjuniorObject("unstable_tile",
                "images/objects/unstable_tile/unstable_tile.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class UnstableTile : SimpleObject
{
	[ChooseResourceSetting]
	[LispChild("sprite")]
	public string SpriteFile {
		get {
			return spriteFile;
		}
		set {
			if (!String.IsNullOrEmpty(value)) {
				Sprite newSprite = SpriteManager.Create(value);
				newSprite.Action = "normal";
				Sprite = newSprite;	//save new sprite after (no exception only)
			}
			spriteFile = value;
		}
	}
	private string spriteFile = "images/objects/unstable_tile/unstable_tile.sprite";

	public UnstableTile() {
		Sprite = SpriteManager.Create("images/objects/unstable_tile/unstable_tile.sprite");
		Sprite.Action = "normal";
	}
}

[TuxjuniorObject("weak_block", "images/objects/strawbox/strawbox.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class WeakBlock : SimpleObject
{
	public WeakBlock() {
		Sprite = SpriteManager.Create("images/objects/strawbox/strawbox.sprite");
		Sprite.Action = "normal";
	}
}

[TuxjuniorObject("infoblock", "images/objects/bonus_block/infoblock.sprite",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class InfoBlock : SimpleObject
{
	[LispChild("message", Translatable = true)]
	[EditScriptSetting]
	public string Message = String.Empty;

	public InfoBlock() {
		Sprite = SpriteManager.Create("images/objects/bonus_block/infoblock.sprite");
	}
}

#endregion TileLike

[TuxjuniorObject("powerup", "images/engine/editor/powerup.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Powerup : SimpleObject
{
	[ChooseResourceSetting]
	[LispChild("sprite")]
	public string SpriteFile {
		get {
			return spriteFile;
		}
		set {
			if (!String.IsNullOrEmpty(value))
				Sprite = SpriteManager.Create(value);
			spriteFile = value;
		}
	}
	private string spriteFile = String.Empty;
	[LispChild("script", Optional = true, Default = "")]
	[EditScriptSetting]
	public string Script = String.Empty;
	[LispChild("disable-physics", Optional = true, Default = false)]
	public bool DisablePhysics;

	public Powerup() {
		Sprite = SpriteManager.CreateFromImage("images/engine/editor/powerup.png");
		Sprite.Action = "default";
	}
}

[TuxjuniorObject("scriptedobject", "images/engine/editor/scriptedobject.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class ScriptedObject : SimpleObject
{
	[PropertyProperties(Tooltip = ToolTipStrings.ScriptingName)]
	[LispChild("name")]
	public string Name = String.Empty;
	[ChooseResourceSetting]
	[LispChild("sprite")]
	public string SpriteFile {
		get {
			return spriteFile;
		}
		set {
			if (!String.IsNullOrEmpty(value))
				Sprite = SpriteManager.Create(value);
			spriteFile = value;
		}
	}
	private string spriteFile = String.Empty;
	[LispChild("z-pos", Optional = true, Default = -10)]
	public int ZPos = -10;
	[LispChild("visible")]
	public bool Visible = true;
	[LispChild("physic-enabled")]
	public bool PhysicEnabled = false;
	[LispChild("solid")]
	public bool Solid = false;

	public ScriptedObject() {
		Sprite = SpriteManager.CreateFromImage("images/engine/editor/scriptedobject.png");
		Sprite.Action = "default";
	}
}

#region AreaObjects

[TuxjuniorObject("wind", "images/engine/editor/wind.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Wind : SimpleObjectArea
{
	[PropertyProperties(Tooltip = ToolTipStrings.ScriptingName)]
	[LispChild("name", Optional = true, Default = "")]
	public string Name = String.Empty;

	[PropertyProperties(Tooltip = "If enabled the wind will be blowing initially.")]
	[LispChild("blowing", Optional = true, Default = true)]
	public bool Blowing = true;

	[LispChild("speed-x")]
	public float SpeedX = 0;

	[LispChild("speed-y")]
	public float SpeedY = 0;

	[LispChild("acceleration")]
	public float Acceleration = 0;

	public Wind() {
		Color = new Drawing.Color(.8f, 0, 0.8f, 0.8f);
	}
}

[TuxjuniorObject("ambient_sound", "images/engine/editor/ambientsound.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class AmbientSound : SimpleObjectArea
{
	[LispChild("sample")]
	[ChooseResourceSetting]
	public string Sample = String.Empty;
	[LispChild("distance_factor")]
	public float DistanceFactor;
	[LispChild("distance_bias")]
	public float DistanceBias;
	[LispChild("volume")]
	public float Volume;
	[PropertyProperties(Tooltip = ToolTipStrings.ScriptingName)]
	[LispChild("name", Optional = true, Default = "")]
	public string Name = String.Empty;

	public AmbientSound() {
		Sprite = SpriteManager.CreateFromImage("images/engine/editor/ambientsound.png");
		Sprite.Action = "default";
		Color = new Drawing.Color(0, 0, 0.8f, 0.8f);
	}
}

[TuxjuniorObject("sequencetrigger", "images/engine/editor/sequencetrigger.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class SequenceTrigger : SimpleObjectArea
{
	[LispChild("sequence")]
	public string Sequence = String.Empty;

	public SequenceTrigger() {
		Color = new Drawing.Color(.8f, 0, 0, 0.8f);
	}
}

[TuxjuniorObject("scripttrigger", "images/engine/editor/scripttrigger.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class ScriptTrigger : SimpleObjectArea
{
	[LispChild("script")]
	[EditScriptSetting]
	public string Script = String.Empty;
	[LispChild("button")]
	public bool IsButton;

	public ScriptTrigger() {
		Color = new Drawing.Color(.8f, 0, .8f, 0.8f);
	}
}

[TuxjuniorObject("invisible_wall", "images/engine/editor/invisible_wall.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class InvisibleWall : SimpleObjectArea
{
	public InvisibleWall() {
		Color = new Drawing.Color(0, .8f, 0, 0.8f);
	}
}

[TuxjuniorObject("secretarea",  "images/engine/editor/secretarea.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class SecretArea : SimpleObjectArea
{
	[PropertyProperties(Tooltip = "Fade the tilemap with this name when the player finds the secret area. Optional.")]
	[LispChild("fade-tilemap", Optional = true, Default = "")]
	public string FadeTilemap = String.Empty;

	public SecretArea() {
		Color = new Drawing.Color(0, .8f, 0, 0.8f);
	}
}

// TODO: This image isn't good for this, make one that fit with the
//       other areas.
[TuxjuniorObject("climbable",  "images/tiles/forest/ladder.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Climbable : SimpleObjectArea
{
	public Climbable() {
		Color = new Drawing.Color(.8f, .8f, 0, 0.8f);
	}
}

#endregion AreaObjects

#region Particles

[TuxjuniorObject("particles-rain", "images/engine/editor/rain.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class RainParticles : IGameObject
{
	[LispChild("z-pos", Optional = true, Default = 0)]
	public int ZPos = 0;
}

[TuxjuniorObject("particles-ghosts", "images/engine/editor/ghostparticles.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class GhostParticles : IGameObject
{
	[LispChild("z-pos", Optional = true, Default = -200)]
	public int ZPos = -200;
}

[TuxjuniorObject("particles-snow", "images/engine/editor/snow.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class SnowParticles : IGameObject
{
	[LispChild("z-pos", Optional = true, Default = -200)]
	public int ZPos = -200;
}

[TuxjuniorObject("particles-clouds", "images/engine/editor/clouds.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class CloudParticles : IGameObject
{
	[LispChild("z-pos", Optional = true, Default = -200)]
	public int ZPos = -200;
}

#endregion Particles

[TuxjuniorObject("leveltime", "images/engine/editor/clock.png",
                Target = TuxjuniorObjectAttribute.Usage.None)]
public sealed class LevelTime : IGameObject
{
	[PropertyProperties(Tooltip = "Time in seconds")]
	[LispChild("time")]
	public float Time;
}

[TuxjuniorObject("thunderstorm", "images/engine/editor/thunderstorm.png",
                Target = TuxjuniorObjectAttribute.Usage.LevelOnly)]
public sealed class Thunderstorm : IGameObject
{
	[PropertyProperties(Tooltip = ToolTipStrings.ScriptingName)]
	[LispChild("name", Optional = true, Default = "")]
	public string Name = String.Empty;

	[PropertyProperties(Tooltip = "If enabled the thunderstorm will be running initially.")]
	[LispChild("running", Optional = true, Default = true)]
	public bool Running = true;

	[PropertyProperties(Tooltip = "Time between last lightning and next thunder")]
	[LispChild("interval", Optional = true, Default = 10f)]
	public float Interval = 10;
}
