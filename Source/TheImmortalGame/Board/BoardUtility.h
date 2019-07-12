#pragma once

#include "Platform.h"

#include "BoardConstants.h"
#include "TileUtility.h"

struct FVector;

namespace BoardUtility
{
	struct TileCoordinate
	{
		const int32 Row = 0;
		const int32 Col = 0;
	};

	struct TileDimensions
	{
		const float TileWidth = DEFAULT_TILE_HEIGHT; 
		const float TileHeight = DEFAULT_TILE_HEIGHT;
	};

	struct BoardDimensions
	{
		const int32 NumRows = DEFAULT_NUM_ROWS;
		const int32 NumCols = DEFAULT_NUM_COLS;
	};

	FVector OriginToTileCentreOffset(TileCoordinate Coordinate, TileDimensions Dimensions = TileDimensions());

	TileUtility::ETileColour CoordinateToTileColour(TileCoordinate Coordinate);

	int32 CoordinateToIndex(TileCoordinate Coordinate, BoardDimensions Dimensions = BoardDimensions());
	TileCoordinate IndexToCoordinate(int32 Index, BoardDimensions Dimensions = BoardDimensions());
}