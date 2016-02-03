//  $Id: Rect.cs 4680 2007-01-26 23:30:11Z anmaster $
using System;
using DataStructures;
using OpenGl;

namespace SceneGraph
{

	/// <summary>
	/// Scene Graph nodes which draws a 2 dimensional rectangle (without
	/// textures, just plain color, filled or not filled)
	/// </summary>
	public sealed class Rectangle : Node
	{
		public RectangleF Rect;
		public bool Fill;

		public Rectangle()
		{
		}

		public void Draw(Gdk.Rectangle cliprect)
		{
			gl.Disable(gl.TEXTURE_2D);
			gl.PolygonMode(gl.FRONT_AND_BACK, Fill ? gl.FILL : gl.LINE);

			gl.Begin(gl.QUADS);
			gl.Vertex2f(Rect.Left, Rect.Top);
			gl.Vertex2f(Rect.Right, Rect.Top);
			gl.Vertex2f(Rect.Right, Rect.Bottom);
			gl.Vertex2f(Rect.Left, Rect.Bottom);
			gl.End();

			gl.PolygonMode(gl.FRONT_AND_BACK, gl.FILL);
			gl.Enable(gl.TEXTURE_2D);
		}
	}

}
