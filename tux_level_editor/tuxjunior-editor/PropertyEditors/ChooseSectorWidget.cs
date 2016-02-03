//  $Id: ChooseSectorWidget.cs 5762 2008-09-01 14:23:39Z mmlosh $
//
//  Copyright (C) 2007 Arvid Norlander <anmaster AT berlios DOT de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using Gtk;
using LispReader;
using Undo;

public sealed class ChooseSectorWidget : CustomSettingsWidget {
	private ComboBox comboBox;
	private List<String> sectorNames;

	public override Widget Create(object caller) {
		HBox box = new HBox();

		PropertiesView propview = (PropertiesView)caller;

		// Add the names of the sectors to a list
		sectorNames = new List<String>(propview.application.CurrentLevel.Sectors.Count);
		foreach(Sector sector in propview.application.CurrentLevel.Sectors) {
			sectorNames.Add(sector.Name);
		}

		// Populate a combo box with the sector names
		comboBox = new ComboBox(sectorNames.ToArray());

		OnFieldChanged(Field); //same code for initialization

		comboBox.Changed += OnComboBoxChanged;
		box.PackStart(comboBox, true, true, 0);

		box.Name = Field.Name;

		CreateToolTip(caller, comboBox);

		return box;
	}

	private void OnComboBoxChanged(object o, EventArgs args) {
		try {
			ComboBox comboBox = (ComboBox)o;
			string newText = comboBox.ActiveText;
			string oldText = (string) Field.GetValue(Object);
			if (newText != oldText) {
				PropertyChangeCommand command = new PropertyChangeCommand(
					"Changed value of " + Field.Name,
					Field,
					Object,
					newText);
				command.Do();
				UndoManager.AddCommand(command);
			}
		} catch (Exception e) {
			ErrorDialog.Exception(e);
		}
	}

	/// <summary> Called when our data changes, use this for re-loading. </summary>
	protected override void OnFieldChanged(FieldOrProperty field) {
		// Get the index of the current value from the original list
		// due to limitations in ComboBox
		string val = (string)Field.GetValue(Object);
		if (val != null)
			comboBox.Active = sectorNames.IndexOf(val);
	}
}

[AttributeUsage(AttributeTargets.Field | AttributeTargets.Property,
								AllowMultiple = false)]
public sealed class ChooseSectorSettingAttribute : CustomSettingsWidgetAttribute {
	public ChooseSectorSettingAttribute()
		: base(typeof(ChooseSectorWidget)) {
	}
}
