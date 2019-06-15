#pragma once

#include "Platform.h"

#include "BoardConstants.h"
#include "TileUtility.h"

struct FVector;

namespace BoardUtility
{
	struct TileCoordinate
	{
		int32 Row = 0;
		int32 Col = 0;
	};

	struct BoardDimensions
	{
		float TileWidth = DEFAULT_TILE_HEIGHT; 
		float TileHeight = DEFAULT_TILE_HEIGHT;
	};

	FVector OriginToTileCentreOffset(TileCoordinate Coordinate, BoardDimensions Dimensions = BoardDimensions());

	TileUtility::ETileColour CoordinateToTileColour(TileCoordinate Coordinate);
}