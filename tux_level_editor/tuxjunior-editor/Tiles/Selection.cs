//  $Id: Selection.cs 4811 2007-02-05 13:26:37Z anmaster $

public sealed class Selection : TileBlock {
	public delegate void ChangedEventHandler();
	public event ChangedEventHandler Changed;

	public void FireChangedEvent() {
		Changed();
	}
}
