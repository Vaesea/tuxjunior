//  $Id: SettingsDialog.cs 4954 2007-03-28 21:16:05Z matzeb $
using System;
using Gtk;
using Gdk;
using Glade;

public class SettingsDialog
{
	[Glade.Widget]
	private Dialog settingsDialog = null;
	[Glade.Widget]
	private Entry entryDataDir = null;
	[Glade.Widget]
	private Entry entryExe = null;

	/// <summary>
	/// Used to show message about the editor needs to be restarted.
	/// </summary>
	private bool Changed;

	public SettingsDialog(bool modal)
	{
		Glade.XML gxml = new Glade.XML("editor.glade", "settingsDialog");
		gxml.Autoconnect(this);

		if(settingsDialog == null || entryDataDir == null || entryExe == null)
			throw new Exception("Couldn't load settings Dialog");

		entryDataDir.Text = Settings.Instance.TuxjuniorData;
		entryExe.Text = Settings.Instance.TuxjuniorExe;

		Changed = false;
		settingsDialog.Icon = EditorStock.WindowIcon;
		if (!modal) {
			settingsDialog.ShowAll();
		} else {
			settingsDialog.Run();
			settingsDialog.Destroy();
		}
	}

	protected void OnEntryDataDirChanged(object o, EventArgs args)
	{
		if (Settings.Instance.TuxjuniorData.TrimEnd(System.IO.Path.DirectorySeparatorChar) != entryDataDir.Text)
			Changed = true;
		Settings.Instance.TuxjuniorData = entryDataDir.Text;
		Settings.Instance.Save();
	}

	protected void OnEntryExeChanged(object o, EventArgs args)
	{
		if (entryExe.Text == null)
			return;
		if (Settings.Instance.TuxjuniorExe != entryExe.Text)
			Changed = true;
		Settings.Instance.TuxjuniorExe = entryExe.Text;
		Settings.Instance.Save();
	}

	protected void OnBtnDataDirBrowseClicked(object o, EventArgs args)
	{
		FileChooserDialog fileChooser = new FileChooserDialog("Locate TuxJunior Data Directory", settingsDialog, FileChooserAction.SelectFolder, new object[] {});
		fileChooser.AddButton(Gtk.Stock.Cancel, Gtk.ResponseType.Cancel);
		fileChooser.AddButton(Gtk.Stock.Ok, Gtk.ResponseType.Ok);
		fileChooser.DefaultResponse = Gtk.ResponseType.Ok;
		if (fileChooser.Run() == (int)ResponseType.Ok) {
			entryDataDir.Text = fileChooser.Filename;
		}
		fileChooser.Destroy();
	}

	protected void OnBtnExeBrowseClicked(object o, EventArgs args)
	{
		FileChooserDialog fileChooser = new FileChooserDialog("Locate TuxJunior Executable", settingsDialog, FileChooserAction.Open, new object[] {});
		fileChooser.AddButton(Gtk.Stock.Cancel, Gtk.ResponseType.Cancel);
		fileChooser.AddButton(Gtk.Stock.Ok, Gtk.ResponseType.Ok);
		fileChooser.DefaultResponse = Gtk.ResponseType.Ok;
		if (fileChooser.Run() == (int)ResponseType.Ok) {
			entryExe.Text = fileChooser.Filename;
		}
		fileChooser.Destroy();
	}

	protected void OnClose(object o, EventArgs args)
	{
		if (Changed) {
			MessageDialog md = new MessageDialog(settingsDialog,
			                                     DialogFlags.DestroyWithParent,
			                                     MessageType.Warning,
			                                     ButtonsType.Ok,
			                                     "You have to restart the editor before the changes take effect.");
			md.Run();
			md.Destroy();
		}

		settingsDialog.Hide();
	}
}
