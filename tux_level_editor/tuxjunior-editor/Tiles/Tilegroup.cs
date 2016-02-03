//  $Id: Tilegroup.cs 4810 2007-02-05 13:09:17Z anmaster $
using System;
using System.Collections.Generic;
using LispReader;

[LispRoot("tilegroup")]
public class Tilegroup
{
	[LispChild("name")]
	public string Name;
	[LispChild("tiles")]
	public List<int> Tiles = new List<int>();

	public Tilegroup()
	{
	}
}
