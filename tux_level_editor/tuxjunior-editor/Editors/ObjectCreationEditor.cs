//  $Id: ObjectCreationEditor.cs 5743 2008-08-25 14:29:54Z mmlosh $
using DataStructures;
using System;
using System.Reflection;
using Gdk;
using OpenGl;
using Sprites;

public sealed class ObjectCreationEditor : ObjectEditorBase, IEditor
{
	private Type objectType;
	// Sprite for this object.
	private Sprite Icon;
	// Position of the mouse
	private Vector MousePos;
	public event RedrawEventHandler Redraw;

	public ObjectCreationEditor(IEditorApplication application,
	                            Sector sector, Type objectType, Sprite Icon) {
		this.application = application;
		this.sector = sector;
		this.objectType = objectType;
		this.Icon = Icon;
	}

	public void Draw(Gdk.Rectangle cliprect)
	{
		Vector pos;
		if( application.SnapToGrid ){
			int snap = 32;
			pos = new Vector((float) ((int)MousePos.X / snap) * snap,
			                 (float) ((int)MousePos.Y / snap) * snap);
		} else {
			pos = MousePos;
		}
		if (Icon != null) {
			gl.Color4f(1, 0, 0, 0.7f);
			//TODO: Make it correct for hitbox coordinates...
			Icon.Draw(pos);
			gl.Color4f(1, 1, 1, 1);
		}
	}

	public void OnMouseButtonPress(Vector mousePos, int button, ModifierType Modifiers)
	{
		if (button == 1){
			IGameObject gameObject = CreateObjectAt(MousePos);

			// switch back to object edit mode when shift was not pressed
			if((Modifiers & ModifierType.ShiftMask) == 0) {
				ObjectsEditor editor = new ObjectsEditor(application, application.CurrentSector);
				if(gameObject is IObject) {
					editor.MakeActive((IObject) gameObject);
				}
				application.SetEditor(editor);
			}
		} else {	//cancel creation by other buttons
			application.SetToolObjects();
		}
		if (UpdateMousePos(mousePos))
			Redraw();
	}

	public void OnMouseButtonRelease(Vector mousePos, int button, ModifierType Modifiers)
	{
		if (UpdateMousePos(mousePos))
			Redraw();
	}

	public void OnMouseMotion(Vector mousePos, ModifierType Modifiers)
	{
		if (UpdateMousePos(mousePos))
			Redraw();
	}

	private IGameObject CreateObjectAt(Vector pos)
	{
		if( application.SnapToGrid ){
			int snap = 32;
			pos = new Vector((float) ((int)pos.X / snap) * snap,
			                 (float) ((int)pos.Y / snap) * snap);
		}
		IGameObject gameObject = (IGameObject) CreateObject();
		if(gameObject is IObject) {
			IObject obj = (IObject) gameObject;
			RectangleF rect = obj.Area;
			rect.MoveTo(pos);
			obj.ChangeArea(rect);
		}
		if(gameObject is IPathObject) {
			Path path = ((IPathObject) gameObject).Path;
			if(path != null) {
				if(path.Nodes.Count == 0) {
					path.Nodes.Add(new Path.Node());
				}
				path.Nodes[0].Pos = pos;
			}
		}

		sector.Add(gameObject, objectType.ToString());
		Redraw();
		return gameObject;
	}

	private bool UpdateMousePos(Vector MousePos) {
		if (this.MousePos != MousePos) {
			this.MousePos = MousePos;
			return true;
		}

		return false;
	}

	private object CreateObject()
	{
		// Create object
		ConstructorInfo Constructor = objectType.GetConstructor(Type.EmptyTypes);
		if(Constructor == null)
			throw new Exception("Type '" + objectType + "' has no public constructor without arguments");
		object Result = Constructor.Invoke(new object[] {});

		return Result;
	}
}
