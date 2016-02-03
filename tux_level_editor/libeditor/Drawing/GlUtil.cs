//  $Id: GlUtil.cs 4507 2006-12-28 14:44:46Z anmaster $
using System;
using OpenGl;
using OpenGlUtil;

namespace Drawing
{

	public static class GlUtil
	{
		/// <summary>set to false if there's no valid opengl context active</summary>
		public static bool ContextValid;

		public static void Assert(string message)
		{
			uint error = gl.GetError();
			if(error != gl.NO_ERROR) {
				throw new Exception("OpenGL error while '" + message + "': "
				                    + glu.ErrorString(error) + " (" + error + ")");
			}
		}
	}

}
