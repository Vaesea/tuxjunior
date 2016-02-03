//  $Id: ChooseResourceWidget.cs 5762 2008-09-01 14:23:39Z mmlosh $
using System;
using System.IO;
using System.Reflection;
using Gtk;
using LispReader;
using Undo;

public sealed class ChooseResourceWidget : CustomSettingsWidget {
	private Entry entry;

	public override Widget Create(object caller) {
		HBox box = new HBox();
		entry = new Entry();
		OnFieldChanged(Field); //same code for initialization

		entry.FocusOutEvent += OnEntryChangeDone;
		box.PackStart(entry, true, true, 0);

		Button chooseButton = new Button("...");
		box.PackStart(chooseButton, false, false, 0);
		chooseButton.Clicked += OnChoose;

		box.Name = Field.Name;

		CreateToolTip(caller, entry);

		return box;
	}

	private void OnChoose(object o, EventArgs args) {
		FileChooserDialog dialog = new FileChooserDialog("Choose resource", null, FileChooserAction.Open, new object[] { });
		dialog.AddButton(Gtk.Stock.Cancel, Gtk.ResponseType.Cancel);
		dialog.AddButton(Gtk.Stock.Open, Gtk.ResponseType.Ok);
		dialog.DefaultResponse = Gtk.ResponseType.Ok;

		dialog.Action = FileChooserAction.Open;
		dialog.SetFilename(Settings.Instance.TuxjuniorData + entry.Text);
		int result = dialog.Run();
		if (result != (int) ResponseType.Ok) {
			dialog.Destroy();
			return;
		}
		string path;
		if (dialog.Filename.StartsWith(Settings.Instance.TuxjuniorData))
			path = dialog.Filename.Substring(Settings.Instance.TuxjuniorData.Length,
																						 dialog.Filename.Length - Settings.Instance.TuxjuniorData.Length);
		else
			path = System.IO.Path.GetFileName(dialog.Filename);
		// Fixes backslashes on windows:
		entry.Text = path.Replace("\\", "/");
		dialog.Destroy();

		OnEntryChangeDone(entry, null);
	}

	private void OnEntryChangeDone(object o, FocusOutEventArgs args) {
		try {
			Entry entry = (Entry) o;
			if ((string)Field.GetValue(Object) == entry.Text) return;
			PropertyChangeCommand command = new PropertyChangeCommand(
				"Changed value of " + Field.Name,
				Field,
				Object,
				entry.Text);
			command.Do();
			UndoManager.AddCommand(command);
		} catch (Exception e) {
			ErrorDialog.Exception(e);
			string val = (string) Field.GetValue(Object);
			if (val != null)
				entry.Text = val;
		}
	}

	/// <summary> Called when our data changes, use this for re-loading. </summary>
	protected override void OnFieldChanged(FieldOrProperty field) {
		string val = (string) Field.GetValue(Object);
		if (val != null)
			entry.Text = val;
		else
			entry.Text = "";
	}
}

[AttributeUsage(AttributeTargets.Field | AttributeTargets.Property,
                AllowMultiple=false)]
public sealed class ChooseResourceSetting : CustomSettingsWidgetAttribute
{
	public ChooseResourceSetting() : base(typeof(ChooseResourceWidget))
	{
	}
}
