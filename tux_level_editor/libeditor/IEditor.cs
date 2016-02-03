//  $Id: IEditor.cs 4760 2007-01-31 18:53:43Z anmaster $
using DataStructures;
using Gdk;
using Gtk;

public interface IEditor
{
	/// <summary>
	/// Draw it
	/// </summary>
	/// <param name="cliprect">
	/// The area that is visible in the <see cref="RenderView"/>
	/// we are drawing to. Check with this to see if you can skip
	/// drawing.
	/// </param>
	void Draw(Gdk.Rectangle cliprect);
	void OnMouseButtonPress(Vector mousePos, int button, ModifierType Modifiers);
	void OnMouseButtonRelease(Vector mousePos, int button, ModifierType Modifiers);
	void OnMouseMotion(Vector mousePos, ModifierType Modifiers);

	event RedrawEventHandler Redraw;
}
public delegate void RedrawEventHandler();

public interface IEditorCursorChange
{
	event CursorChangeHandler CursorChange;
}
public delegate void CursorChangeHandler(Cursor cursor);
