//  $Id: ChooseColorWidget.cs 5758 2008-08-30 21:29:50Z mmlosh $
using System;
using Drawing;
using Gtk;
using Gdk;
using LispReader;
using Undo;

/// <summary>
/// Colour choosing widget for properties.
/// </summary>
public sealed class ChooseColorWidget : CustomSettingsWidget
{
	private ColorButton colorButton;

	/// <summary>Should we let the user set the alpha?</summary>
	private bool useAlpha;

	public ChooseColorWidget()
	{
	}

	public override Widget Create(object caller)
	{
		colorButton = new ColorButton();

		//Console.WriteLine("ChooseColorWidget Create val {0},{1},{2},{3}", val.Red, val.Green, val.Blue, val.Alpha);
		// Get if we should use alpha
		ChooseColorSettingAttribute chooseColorSetting = (ChooseColorSettingAttribute)
			Field.GetCustomAttribute(typeof(ChooseColorSettingAttribute));
		useAlpha = chooseColorSetting.UseAlpha;

		if (useAlpha)
			colorButton.UseAlpha = true;

		OnFieldChanged(Field);

		colorButton.ColorSet += OnChooseColor;

		colorButton.Name = Field.Name;

		// Create a tooltip if we can.
		CreateToolTip(caller, colorButton);

		return colorButton;
	}

	protected override void OnFieldChanged(FieldOrProperty field) {
		Drawing.Color val = (Drawing.Color) Field.GetValue(Object);

		Gdk.Color color = new Gdk.Color();
		color.Red = (ushort) (val.Red * 65535f);
		color.Green = (ushort) (val.Green * 65535f);
		color.Blue = (ushort) (val.Blue * 65535f);

		if (useAlpha)
			colorButton.Alpha = (ushort) (val.Alpha * 65535f);

		colorButton.Color = color;
	}

	private void OnChooseColor(object sender, EventArgs args)
	{
		Drawing.Color col = new Drawing.Color();
		col.Red = ((float) colorButton.Color.Red) / 65535f;
		col.Blue = ((float) colorButton.Color.Blue) / 65535f;
		col.Green = ((float) colorButton.Color.Green) / 65535f;
		col.Alpha = 1f;
		if (useAlpha)
			col.Alpha = ((float) colorButton.Alpha) / 65535f;

		if (col != (Drawing.Color) Field.GetValue(Object)) {
			PropertyChangeCommand command = new PropertyChangeCommand(
				"Changed value of " + Field.Name,
				Field,
				Object,
				col);
			command.Do();
			UndoManager.AddCommand(command);
			//Console.WriteLine("ChooseColorWidget change col r{0},g{1},b{2},a{3}", col.Red, col.Green, col.Blue, col.Alpha);
			//Console.WriteLine("ChooseColorWidget change gtk color r{0},g{1},b{2},a{3}", colorButton.Color.Red, colorButton.Color.Green, colorButton.Color.Blue, colorButton.Alpha);
		}
	}
}

[AttributeUsage(AttributeTargets.Field | AttributeTargets.Property,
                AllowMultiple=false)]
public sealed class ChooseColorSettingAttribute : CustomSettingsWidgetAttribute
{
	/// <summary>Should we let the user set the alpha?</summary>
	public bool UseAlpha = false;

	public ChooseColorSettingAttribute() : base(typeof(ChooseColorWidget))
	{
	}
}
