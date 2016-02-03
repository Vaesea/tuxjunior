//  $Id: ICustomSettingsWidget.cs 5761 2008-08-31 19:32:56Z mmlosh $
using System;
using System.Reflection;
using Gtk;
using LispReader;

public interface ICustomSettingsWidget
{
	Widget Create(object caller, object Object, FieldOrProperty Field);
	void ChangeObject (object Object);
}
