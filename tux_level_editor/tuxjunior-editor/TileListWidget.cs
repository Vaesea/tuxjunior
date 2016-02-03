//  $Id: TileListWidget.cs 5716 2008-08-03 17:57:38Z wolfgangb $
using System;
using System.Collections.Generic;
using Gtk;
using Gdk;
using OpenGl;
using Drawing;
using SceneGraph;
using DataStructures;

public class TileListWidget : GLWidgetBase {
	private Tileset tileset;
	private Tilegroup tilegroup;
	private Selection selection;
	private Level level;

	private const int TILE_WIDTH = 32;
	private const int TILE_HEIGHT = 32;
	private const int SPACING_X = 1;
	private const int SPACING_Y = 1;
	private const int ROW_HEIGHT = TILE_HEIGHT + SPACING_Y;
	private const int COLUMN_WIDTH = TILE_WIDTH + SPACING_X;
	private const int TILES_PER_ROW = 4;

	private int hovertile = -1;
	private Vector StartPos;
	private bool multiselectInProgress = false;
	
	private Adjustment vadjustment;
	
	private IEditorApplication application;

	public TileListWidget(IEditorApplication application, Selection selection, Adjustment adjv)
	{
		this.selection = selection;
		selection.Changed += OnSelectionChanged;
		this.application = application;

		Tileset.LoadEditorImages = true;
		SetSizeRequest((TILE_WIDTH + SPACING_X) * TILES_PER_ROW, -1);

		ButtonPressEvent += OnButtonPress;
		ButtonReleaseEvent += OnButtonRelease;
		MotionNotifyEvent += OnMotionNotify;
		ScrollEvent += OnScroll;

		AddEvents((int) Gdk.EventMask.ButtonPressMask);
		AddEvents((int) Gdk.EventMask.ButtonReleaseMask);
		AddEvents((int) Gdk.EventMask.PointerMotionMask);
		AddEvents((int) Gdk.EventMask.ScrollMask);

		SizeAllocated += OnSizeAllocated;
		application.LevelChanged += OnLevelChanged;
		
		vadjustment = adjv;
		vadjustment.ValueChanged += OnVAdjustmentChangedValue;
	}

	public void ChangeTilegroup(Tilegroup tilegroup)
	{
		this.tilegroup = tilegroup;
		Translation = new Vector(0, 0);
		vadjustment.Value = -Translation.Y;
		Zoom = 1.0f;
		hovertile = -1;
		updateScrollbar();
		QueueDraw();
	}

	private void OnLevelChanged(Level level)
	{
		if(this.level != null)
			this.level.TilesetChanged -= OnTilesetChanged;
		if(level != null)
			level.TilesetChanged += OnTilesetChanged;

		this.level = level;
		OnTilesetChanged(level);
	}

	private void OnTilesetChanged(Level level)
	{
		tileset = level.Tileset;
		Translation = new Vector(0, 0);
		vadjustment.Value = -Translation.Y;
		Zoom = 1.0f;

		tilegroup = tileset.Tilegroups["All"];
		updateScrollbar();
		
		QueueDraw();
	}

	private void OnSelectionChanged()
	{
		QueueDraw();

		if( selection.Width == 1 && selection.Height == 1 ){
			int selectedTileID = selection[0, 0]; 
			string attributes;
			if( level.isWorldmap ){
				attributes = tileset.Get( selectedTileID ).ParseWorldmapAttributes();
			} else {
				attributes = tileset.Get( selectedTileID ).ParseLevelAttributes();
			}	
			application.PrintStatus( "TileListWidget: Selected tile: " + selectedTileID + " Attributes: " + attributes);
		} else if( selection.Width <= 0 || selection.Height <= 0 ){
			application.PrintStatus( "TileListWidget: No tile selected tile." );
		} else {
			application.PrintStatus( "TileListWidget: [" + selection.Width
			                         + "x" + selection.Height + "] tiles selected." );
		}
	}

	protected override void DrawGl()
	{
		if(tileset == null)
			return;

		gl.Clear(gl.COLOR_BUFFER_BIT);

		int starttile = (int) -Translation.Y / (ROW_HEIGHT)
		                * TILES_PER_ROW;
		Vector pos = new Vector(0,
		                        (starttile / TILES_PER_ROW) * (ROW_HEIGHT));
		float maxwidth = (TILE_WIDTH + SPACING_X) * TILES_PER_ROW;
		List<int> tiles = tilegroup.Tiles;
		for(int i = starttile; i < tiles.Count; i++) {
			Tile tile = tileset.Get(tiles[i]);

			tile.DrawEditor(pos);
			bool selected = IsSelected( tiles[i] );

			if(i == hovertile || selected) {
				if(selected)
					gl.Color4f(0, 0, 1, 0.4f);
				else
					gl.Color4f(0, 0, 1, 0.08f);
				gl.Disable(gl.TEXTURE_2D);
				gl.Begin(gl.QUADS);
				gl.Vertex2f(pos.X, pos.Y);
				gl.Vertex2f(pos.X + TILE_WIDTH, pos.Y);
				gl.Vertex2f(pos.X + TILE_WIDTH, pos.Y + TILE_HEIGHT);
				gl.Vertex2f(pos.X, pos.Y + TILE_HEIGHT);
				gl.End();
				gl.Enable(gl.TEXTURE_2D);
				gl.Color4f(1, 1, 1, 1);
			}
			pos.X += TILE_WIDTH + SPACING_X;
			if(pos.X >= maxwidth) {
				pos.X = 0;
				pos.Y += ROW_HEIGHT;
				if(pos.Y + Translation.Y > Allocation.Height)
					break;
			}
		}
	}

	private void OnButtonPress(object o, ButtonPressEventArgs args)
	{
		if(args.Event.Button == 1) {
			if(tilegroup == null)
				return;

			Vector MousePos = new Vector((float) args.Event.X,
			                             (float) args.Event.Y);
			int tile = PosToTile(MousePos);
			if(tile < 0)
				return;

			selection.Resize(1, 1, 0);
			selection[0, 0] = tilegroup.Tiles[tile];
			selection.FireChangedEvent();
			QueueDraw();
		}

		if(args.Event.Button == 3) {
			if(tilegroup == null)
				return;
			StartPos = new Vector((float) args.Event.X,
			                      (float) args.Event.Y);
			application.PrintStatus( "selecting..." );
			multiselectInProgress = true;
		}
	}

	private void OnButtonRelease(object o, ButtonReleaseEventArgs args)
	{
		//Select all tile in rectangle by dragging right mouse button
		if(args.Event.Button == 3) {
			if(tilegroup == null)
				return;

			application.PrintStatus( "selecting done" );
			Vector MousePos = new Vector((float) args.Event.X,
			                             (float) args.Event.Y);
			MultiSelect( MousePos, StartPos );
			multiselectInProgress = false;
		}
	}

	/// <summary>Test if tile is selected</summary>
	private bool IsSelected( int tile ){
		for( int y = 0; y < selection.Height; y++ ){
			for ( int x = 0; x < selection.Width; x++ ){
				if ( tile == selection[x, y]) {
					return true;
				}
			}
		}
		return false;
	}

	/// <summary>select all Tiles in are between pos1 and pos2</summary>
	private void MultiSelect( Vector pos1, Vector pos2 )
	{
		Vector upperLeft, lowerRight, lowerLeft;
			if( pos1.X < pos2.X ){
				upperLeft.X = pos1.X;
				lowerRight.X = pos2.X;
			} else {
				upperLeft.X = pos2.X;
				lowerRight.X = pos1.X;
			}

			if( pos1.Y < pos2.Y ){
				upperLeft.Y = pos1.Y;
				lowerRight.Y = pos2.Y;
			} else {
				upperLeft.Y = pos2.Y;
				lowerRight.Y = pos1.Y;
			}
			lowerLeft.X = upperLeft.X;
			lowerLeft.Y = lowerRight.Y;

			int tile1 = PosToTile(upperLeft);
			int tile2 = PosToTile(lowerRight);
			int tile3 = PosToTile(lowerLeft);
			if(tile1 < 0 || tile2 < 0 || tile3 < 0 )
				return;

			int startcolumn, endcolumn, width, height;

			//That's how much Tiles?
			/*
			        1 x x
			        x x x
			        3 x 2
			*/

			Math.DivRem( tile1, TILES_PER_ROW, out startcolumn );
			Math.DivRem( tile2, TILES_PER_ROW, out endcolumn );
			width = 1 + endcolumn - startcolumn;
			height = 1 + (( tile3 - tile1 ) / TILES_PER_ROW );
			//sanity check
			if( width < 1 || height < 1 )
				return;
			selection.Resize( (uint) width, (uint) height, 0);
			for( int y = 0; y < height; y++ ) {
				for( int x = 0; x < width; x++ ) {
					selection[ x, y] = tilegroup.Tiles[ tile1 + x + TILES_PER_ROW * y ];
				}
			}
			selection.FireChangedEvent();
			QueueDraw();
	}

	private void OnMotionNotify(object o, MotionNotifyEventArgs args)
	{
		if(tilegroup == null)
			return;

		Vector MousePos = new Vector((float) args.Event.X,
		                             (float) args.Event.Y);
		int newtile = PosToTile(MousePos);
		if(newtile != hovertile) {
			if( multiselectInProgress ){
				MultiSelect( MousePos, StartPos );
			} else {
				QueueDraw();
			}
		}
		hovertile = newtile;
	}

	private int PosToTile(Vector pos)
	{
		int tile = (int) (pos.Y - Translation.Y) / ROW_HEIGHT * TILES_PER_ROW
			+ (int) (pos.X - Translation.X) / COLUMN_WIDTH;
		if(tile < 0) {
			LogManager.Log(LogLevel.Warning, "PosToTile < 0?!?");
			return -1;
		}
		if(tile >= tilegroup.Tiles.Count)
			return -1;

		return tile;
	}

	private void OnScroll(object o, ScrollEventArgs args)
	{
		if(args.Event.Direction == ScrollDirection.Up &&
		   Translation.Y <= (float) -ROW_HEIGHT) {
			Translation = Translation + new Vector(0, ROW_HEIGHT - (Translation.Y%ROW_HEIGHT));
			vadjustment.Value = -Translation.Y;
			args.RetVal = true;
		} else if(args.Event.Direction == ScrollDirection.Down &&
		   Translation.Y - ROW_HEIGHT > -ROW_HEIGHT * Math.Floor( (double)tilegroup.Tiles.Count / (double)TILES_PER_ROW)){
			Translation = Translation - new Vector(0, ROW_HEIGHT - (Translation.Y%ROW_HEIGHT));
			vadjustment.Value = -Translation.Y;
			args.RetVal = true;
		}
	}
	
	/// <summary>Vertical Scroll Bar was scrolled</summary>
	private void OnVAdjustmentChangedValue(object sender, EventArgs e)
	{
		Translation = new Vector(0, (float) -vadjustment.Value);
		QueueDraw();
	}	
	
	/// <summary>adjust the scrollbar</summary>
	private void updateScrollbar()
	{
		if( tilegroup != null ){
			double pageheight =  Allocation.Height - (Allocation.Height%ROW_HEIGHT);
			double upper = (ROW_HEIGHT * Math.Ceiling( (double)tilegroup.Tiles.Count / (double)TILES_PER_ROW ));
			vadjustment.SetBounds(0, upper, ROW_HEIGHT, pageheight - ROW_HEIGHT, pageheight);
		}
	}

	/// <summary>Calculate Scrollbars again for new height</summary>
	private void OnSizeAllocated  (object o, SizeAllocatedArgs args)
	{
		updateScrollbar();
	}
}
