//  $Id: CustomSettingsWidgetAttribute.cs 4811 2007-02-05 13:26:37Z anmaster $
using System;

/// <summary>
/// Base class for custom settings widgets.
/// </summary>
public abstract class CustomSettingsWidgetAttribute : Attribute
{
	public Type Type;

	protected CustomSettingsWidgetAttribute(Type type)
	{
		this.Type = type;
	}
}
