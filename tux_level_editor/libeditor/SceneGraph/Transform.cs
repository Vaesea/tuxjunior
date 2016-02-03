//  $Id: Transform.cs 4680 2007-01-26 23:30:11Z anmaster $
using System;
using DataStructures;
using OpenGl;

namespace SceneGraph
{

	/// <summary>
	/// A scene graph node which applies a transform to the current opengl
	/// transform (the matrix will be multiplied with the currently active
	/// tranform)
	/// </summary>
	public sealed class Transform : NodeWithChilds
	{
		public Matrix Matrix;

		public override unsafe void Draw(Gdk.Rectangle cliprect)
		{
			gl.PushMatrix();
			gl.MultMatrixf(Matrix.Elements);

			DrawChilds(cliprect);

			gl.PopMatrix();
		}
	}

}
