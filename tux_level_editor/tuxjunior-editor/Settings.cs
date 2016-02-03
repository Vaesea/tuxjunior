//  $Id: Settings.cs 5523 2008-06-02 21:14:17Z sommer $
using System;
using System.IO;
using System.Xml;
using System.Xml.Serialization;
using System.Collections.Generic;
using Gtk;
using Gdk;
using Glade;

public sealed class Settings {
	public string LastDirectoryName;
	public string LastBrushDir = "/usr/share/games/tuxjunior-editor/brushes";
	public string TuxjuniorExe = "/usr/games/tuxjunior";
	public string TuxjuniorData = "/usr/share/games/tuxjunior";
	public List<string> RecentDocuments;

	public static Settings Instance;
	private static XmlSerializer settingsSerializer = new XmlSerializer(typeof(Settings));
	private static string SettingsFile;

	static Settings() {
		String SettingsPath = System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), Constants.PACKAGE_NAME);
		SettingsFile = System.IO.Path.Combine(SettingsPath, "settings.xml");

		StreamReader reader = null;
		try {
			LogManager.Log(LogLevel.Info, "Using configfile: " + SettingsFile);
			reader = new StreamReader(SettingsFile);
			Instance = (Settings) settingsSerializer.Deserialize(reader);
		} catch(Exception e) {
			LogManager.Log(LogLevel.Error, "Couldn't load configfile: " + e.Message);
			LogManager.Log(LogLevel.Info, "Creating new config from scratch");
			Instance = new Settings();
		} finally {
			if(reader != null)
				reader.Close();
		}

		if(!Instance.TuxjuniorData.EndsWith(System.IO.Path.DirectorySeparatorChar.ToString())) {
			Instance.TuxjuniorData += System.IO.Path.DirectorySeparatorChar;
		}

		LogManager.Log(LogLevel.Info, "Tuxjunior is run as: " + Instance.TuxjuniorExe);
		LogManager.Log(LogLevel.Info, "Data files are in: " + Instance.TuxjuniorData);

		// If data path does not exist, prompt user to change it before we try continue initializing
		if (!new DirectoryInfo(System.IO.Path.GetDirectoryName(Instance.TuxjuniorData)).Exists) {
			LogManager.Log(LogLevel.Error, "Data path does not exist.");
			MessageDialog md = new MessageDialog(null, DialogFlags.DestroyWithParent, MessageType.Warning, ButtonsType.None, "The current data path, \"" + Instance.TuxjuniorData + "\", does not exist." + Environment.NewLine + Environment.NewLine + "Edit the settings to set a valid data path.");
			md.AddButton(Gtk.Stock.No, ResponseType.No);
			md.AddButton(Gtk.Stock.Edit, ResponseType.Yes);
			if (md.Run() == (int)ResponseType.Yes) {
				new SettingsDialog(true);
			}
			md.Destroy();
		}

		Resources.ResourceManager.Instance = new Resources.DefaultResourceManager(Instance.TuxjuniorData + "/");
	}

	public Settings() {
		// Get default values from the register on Windows.
		// Values read here will be overwritten by the settings file if it exist.
#if WINDOWS
		string TuxjuniorDir = (string)Microsoft.Win32.Registry.GetValue(
			"HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{4BEF4147-E17A-4848-BDC4-60A0AAC70F2A}_is1",
			"Inno Setup: App Path", null);
		if (TuxjuniorDir == null)
			TuxjuniorDir = Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles) + "\\TuxJunior-0.3";
		TuxjuniorExe = TuxjuniorDir + "\\TuxJunior2.exe";
		TuxjuniorData = TuxjuniorDir + "\\data\\";
#endif
	}

	public void Save() {
		StreamWriter writer = null;
		try {
			string dir = System.IO.Path.GetDirectoryName(SettingsFile);
			DirectoryInfo d = new DirectoryInfo(dir);
			if(!d.Exists) {
				LogManager.Log(LogLevel.Info, "Settings path \"" + dir + "\" does not exist. Trying to create.");
				d.Create();
			}

			writer = new StreamWriter(SettingsFile);
			settingsSerializer.Serialize(writer, Instance);
		} catch(Exception e) {
			LogManager.Log(LogLevel.Error, "Couldn't write configfile: " + e.Message);
		} finally {
			if(writer != null)
				writer.Close();
		}
	}

	public void addToRecentDocuments(string fileName) {
		RecentDocuments.RemoveAll(delegate(string s) { return (s == fileName); });
		RecentDocuments.Add(fileName);
		while (RecentDocuments.Count > 8) RecentDocuments.RemoveAt(0);
	}

}
