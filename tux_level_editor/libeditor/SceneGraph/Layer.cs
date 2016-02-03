//  $Id: Layer.cs 4703 2007-01-28 13:44:03Z anmaster $
using System;
using System.Collections.Generic;
using System.Collections;

namespace SceneGraph
{

	/// <summary>
	/// A scene graph node which organizes it's childs in layers
	/// You can put a child in a layer. The layers are drawn in ascending order
	/// ("You can place stuff in foreground and background layers")
	/// </summary>
	public sealed class Layer : Node
	{
		private SortedList Layers = new SortedList();

		public void Add(float Layer, Node Child)
		{
			if(Layers[Layer] == null)
				Layers[Layer] = new List<Node>();
			List<Node> Childs = (List<Node>) Layers[Layer];
			Childs.Add(Child);
		}

		public void Remove(float Layer, Node Child)
		{
			if(Layers[Layer] == null)
				throw new Exception("Specified Layer is empty");
			List<Node> Childs = (List<Node>) Layers[Layer];
			Childs.Remove(Child);
		}

		public void Clear()
		{
			Layers.Clear();
		}

		public void Draw(Gdk.Rectangle cliprect)
		{
			foreach(DictionaryEntry Entry in Layers) {
				List<Node> List = (List<Node>) Entry.Value;
				foreach(Node Child in List) {
					Child.Draw(cliprect);
				}
			}
		}
	}

}
