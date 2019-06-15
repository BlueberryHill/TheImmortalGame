#include "BoardUtility.h"

#include "General/MathHelpers.h"

namespace
{
	bool IsDarkTile(BoardUtility::TileCoordinate Coordinate)
	{
		using namespace Maths;

		int32 Row = Coordinate.Row;
		int32 Col = Coordinate.Col;

		return (IsEven(Row) && IsOdd(Col)) || (IsOdd(Row) && IsEven(Col));
	}
}

namespace BoardUtility
{
	FVector OriginToTileCentreOffset(TileCoordinate Coordinates, BoardDimensions Dimensions /*= BoardDimensions()*/)
	{
		return FVector(static_cast<float>(Coordinates.Row) * Dimensions.TileHeight, 
					   static_cast<float>(Coordinates.Col) * Dimensions.TileWidth, 
					   0.0f);
	}


	TileUtility::ETileColour CoordinateToTileColour(TileCoordinate Coordinate)
	{
		if (IsDarkTile(Coordinate))
		{
			return TileUtility::ETileColour::DARK;
		}
		else
		{
			return TileUtility::ETileColour::LIGHT;
		}
	}
}