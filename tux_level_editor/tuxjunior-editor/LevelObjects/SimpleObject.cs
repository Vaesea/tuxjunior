//  $Id: SimpleObject.cs 5715 2008-08-03 14:38:07Z mmlosh $
using DataStructures;
using Sprites;
using System;
using Lisp;
using LispReader;
using Drawing;
using OpenGl;
using SceneGraph;

/// <summary>Base class for objects in levels</summary>
public abstract class SimpleObject : IGameObject, IObject, Node, ICloneable {
	[PropertyProperties(Tooltip = "X position of object")]
	[LispChild("x")]
	public float X;
	[PropertyProperties(Tooltip = "Y position of object")]
	[LispChild("y")]
	public float Y;

	public virtual RectangleF Area {
		get {
			if(Sprite != null)
				return new RectangleF(X - Sprite.Offset.X, Y - Sprite.Offset.Y,
				                          Sprite.Width, Sprite.Height);
			else
				return new RectangleF(X, Y, 32, 32);
		}
	}

	/// <summary>
	/// If true object is resizable.
	/// </summary>
	public virtual bool Resizable {
		get {
			return false;
		}
	}

	private Sprite sprite;
	protected Sprite Sprite {
		get {
			return sprite;
		}
		set {
			sprite = value;
		}
	}

	public virtual void ChangeArea(RectangleF NewArea) {
		X = NewArea.Left;
		Y = NewArea.Top;
		if(Sprite != null) {
			X += Sprite.Offset.X;
			Y += Sprite.Offset.Y;
		}
	}

	public virtual void Draw(Gdk.Rectangle cliprect) {
		if(Sprite == null)
			return;
		if (cliprect.IntersectsWith((Gdk.Rectangle) Area))
			Sprite.Draw(new Vector(X, Y));
	}

	public virtual Node GetSceneGraphNode() {
		return this;
	}

	public virtual object Clone() {
		return MemberwiseClone();
	}
}


/// <summary>Base class for objects that draw a color box.</summary>
public abstract class SimpleColorObject : SimpleObject
{
	public virtual void DrawColor(Drawing.Color color) {
		//draw a color rectangle
		float left = X + 8;
		float right = X + 24;
		float top = Y + 8;
		float bottom = Y + 24;

		float[] current_color = new float[4];
		gl.GetFloatv( gl.CURRENT_COLOR, current_color );
		//get current color, might be transparent
		gl.Color4f(color.Red, color.Green, color.Blue, color.Alpha*current_color[3]);
		gl.Disable(gl.TEXTURE_2D);

		gl.Begin(gl.QUADS);
		gl.Vertex2f(left, top);
		gl.Vertex2f(right, top);
		gl.Vertex2f(right, bottom);
		gl.Vertex2f(left, bottom);
		gl.End();

		gl.Enable(gl.TEXTURE_2D);
		gl.Color4fv( current_color );
	}
}


/// <summary>Base class for objects with a direction. (Like most badguys)</summary>
public abstract class SimpleDirObject : SimpleObject
{
	public enum Directions {
		/// <summary>
		/// Automatic.
		/// </summary>
		auto,
		/// <summary>
		/// Start out turend towards left side.
		/// </summary>
		left,
		/// <summary>
		/// Start out turend towards right side.
		/// </summary>
		right
	}

	// Override to change sprite on direction change.
	protected virtual void DirectionChanged () {
		string oldaction = Sprite.Action;
		if (direction == Directions.right) {
			try { Sprite.Action = "right"; }
			catch { try { Sprite.Action = "walking-right"; }
				catch {
					LogManager.Log(LogLevel.Warning, "SimpleDirObject: No action found for object.");
					Sprite.Action = oldaction;
				}
			}
		} else {
			try { Sprite.Action = "left"; }
			catch { try { Sprite.Action = "walking-left"; }
				catch {
					LogManager.Log(LogLevel.Warning, "SimpleDirObject: No action found for object.");
					Sprite.Action = oldaction;
				}
			}
		}
	}

	protected Directions direction = Directions.auto;

	/// <summary>
	/// Direction the badguy will be facing initially.
	/// </summary>
	[PropertyProperties(Tooltip = "Direction the badguy will be facing initially.")]
	[LispChild("direction", Optional = true, Default = Directions.auto)]
	public Directions Direction {
		get {
			return direction;
		}
		set {
			direction = value;
			DirectionChanged();
		}
	}

	[LispChild("dead-script", Optional = true, Default = "")]
	[EditScriptSetting]
	public String DeadScript = String.Empty;
}

/// <summary>Base class for platforms and other moving objects.</summary>
public abstract class SimplePathObject : SimpleObject, IPathObject
{
	[PropertyProperties(Tooltip = ToolTipStrings.ScriptingName)]
	[LispChild("name", Optional = true, Default = "")]
	public string Name = String.Empty;
	[PropertyProperties(Tooltip = "If enabled the platform will be moving initially.")]
	[LispChild("running", Optional = true, Default = true)]
	public bool Running = true;
	[ChooseResourceSetting]
	[LispChild("sprite")]
	public string SpriteFile {
		get {
			return spriteFile;
		}
		set {
			if(! String.IsNullOrEmpty(value))
				Sprite = SpriteManager.Create(value);
			spriteFile = value;
		}
	}
	private string spriteFile;

	private Path path = new Path();
	[LispChild("path")]
	public Path Path {
		get {
			return path;
		}
		set {
			path = value;
		}
	}

	public SimplePathObject()
	{
		path.Nodes.Add(new Path.Node());
	}

	public override void ChangeArea(RectangleF NewArea) {
		base.ChangeArea(NewArea);
		Vector translation = new Vector(NewArea.Left - Path.Nodes[0].X,
		                                NewArea.Top - Path.Nodes[0].Y);
		Path.Move(translation);
	}

	public override RectangleF Area {
		get {
			X = Path.Nodes[0].X;	//object is always at the first path node
			Y = Path.Nodes[0].Y;

			return base.Area;
		}
	}

	public override object Clone() {
		SimplePathObject aClone = (SimplePathObject) MemberwiseClone();
		aClone.Path = new Path();
		foreach(Path.Node node in this.Path.Nodes) {
			aClone.Path.Nodes.Add((Path.Node) node.Clone());
		}
		return aClone;
	}
}

/// <summary>Base class for area objects in levels</summary>
public abstract class SimpleObjectArea : SimpleObject
{
	[PropertyProperties(Tooltip = "How wide the object is.")]
	[LispChild("width")]
	public float Width = 32;
	[PropertyProperties(Tooltip = "How high the object is.")]
	[LispChild("height")]
	public float Height = 32;

	protected Drawing.Color Color;

	public override RectangleF Area {
		get {
			return new RectangleF(X, Y, Width, Height);
		}
	}

	/// <summary>
	/// If true object is resizable.
	/// </summary>
	public sealed override bool Resizable {
		get {
			return true;
		}
	}

	public override void Draw(Gdk.Rectangle cliprect) {
		if (!cliprect.IntersectsWith(new Gdk.Rectangle((int) X, (int) Y, (int) Width, (int) Height)))
			return;
		float left = X;
		float right = X + Width;
		float top = Y;
		float bottom = Y + Height;

		float[] current_color = new float[4];
		gl.GetFloatv( gl.CURRENT_COLOR, current_color );
		//get current color, might be transparent
		gl.Color4f(Color.Red, Color.Green, Color.Blue, current_color[3] * Color.Alpha);
		gl.Disable(gl.TEXTURE_2D);

		gl.Begin(gl.QUADS);
		gl.Vertex2f(left, top);
		gl.Vertex2f(right, top);
		gl.Vertex2f(right, bottom);
		gl.Vertex2f(left, bottom);
		gl.End();

		gl.Enable(gl.TEXTURE_2D);
		gl.Color4fv( current_color );
	}

	public override void ChangeArea(RectangleF NewArea) {
		X = NewArea.Left;
		Y = NewArea.Top;
		Width = NewArea.Width;
		Height = NewArea.Height;
	}

	public sealed override Node GetSceneGraphNode() {
		return this;
	}
}
