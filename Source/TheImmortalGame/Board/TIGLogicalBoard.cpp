// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGLogicalBoard.h"

#include "TIGLogicalTile.h"

#include "Game Systems/Movement/MovementUtility.h"

TIGLogicalBoard::TIGLogicalBoard(BoardUtility::BoardDimensions InitDimensions) :
	Dimensions(std::move(InitDimensions))
{
	InitBoard();
}

void TIGLogicalBoard::InitBoard()
{
	GameBoard.Reserve(Dimensions.NumRows);
	for (int32 Row = 0; Row < Dimensions.NumRows; ++Row)
	{
		GameBoard.Emplace(TileRow());
		GameBoard[Row].Reserve(Dimensions.NumCols);
		for (int32 Col = 0; Col < Dimensions.NumCols; ++Col)
		{
			GameBoard[Row].Emplace(MakeUnique<Tile>(TIGLogicalTile::GetInvalidTile()));
		}
	}
}

bool TIGLogicalBoard::IsValidCoordinate(BoardUtility::TileCoordinate Coordinate) const
{
	bool IsValidRow = Coordinate.Row < GetNumRows() && Coordinate.Row >= 0;
	bool IsValidCol = Coordinate.Col < GetNumCols() && Coordinate.Col >= 0;
	return IsValidRow && IsValidCol;
}

BoardUtility::TileCoordinate TIGLogicalBoard::TileToCoordinate(const TIGLogicalTile & Tile) const
{
	for (int32 Row = 0; Row < GetNumRows(); ++Row)
	{
		for (int32 Col = 0; Col < GetNumCols(); ++Col)
		{
			if (GameBoard[Row][Col]->GetUniqueID() == Tile.GetUniqueID())
			{
				return { Row, Col };
			}
		}
	}
	checkNoEntry();
	return BoardUtility::TileCoordinate();
}

TIGLogicalBoard::~TIGLogicalBoard()
{
}

void TIGLogicalBoard::GetNextNTiles(const TIGLogicalTile& From, MovementUtility::EDirection Direction, int32 N, TArray<TIG::TileID>& OutTileArray) const
{
	const BoardUtility::TileCoordinate StartingCoordinate = TileToCoordinate(From);
	BoardUtility::TileCoordinate NextCoordinate = StartingCoordinate;
	for (int32 NumberOfTilesSearched = 0; NumberOfTilesSearched < N; ++NumberOfTilesSearched)
	{
		IncrementCoordinate(NextCoordinate, Direction);
		if (!IsValidCoordinate(NextCoordinate))
		{
			break;
		}

		OutTileArray.Add(GetTileAtCoordinate(NextCoordinate));
	}
}

void TIGLogicalBoard::GetNextNTiles(TIG::TileID From, MovementUtility::EDirection Direction, int32 N, TArray<TIG::TileID>& OutTileArray) const
{
	const TIGLogicalTile& FromTile = GetTileForID(From);
	GetNextNTiles(FromTile, Direction, N, OutTileArray);
}

TIG::TileID TIGLogicalBoard::GetTileInDirection(TIG::TileID From, MovementUtility::EDirection Direction, int32 NumberOfTilesAway)
{
	const TIGLogicalTile& FromTile = GetTileForID(From);
	return GetTileInDirection(FromTile, Direction, NumberOfTilesAway);
}

TIG::TileID TIGLogicalBoard::GetTileInDirection(const TIGLogicalTile & From, MovementUtility::EDirection Direction, int32 NumberOfTilesAway)
{
	BoardUtility::TileCoordinate Coordinate = TileToCoordinate(From);
	IncrementCoordinate(Coordinate, Direction, NumberOfTilesAway);
	if (IsValidCoordinate(Coordinate))
	{
		return GetTileAtCoordinate(Coordinate);
	}
	else
	{
		return TIG::INVALID_TILE_ID;
	}
}

const TIGLogicalTile& TIGLogicalBoard::AddTile(int32 Row, int32 Col)
{
	check(GameBoard[Row][Col] && GameBoard[Row][Col]->GetUniqueID() == -1 && "AddTile() - Board has not been initialised correctly");
	TUniquePtr<Tile> NewTile = MakeUnique<Tile>();
	TileIDToTile.Emplace(NewTile->GetUniqueID(), NewTile.Get());
	NewTile->SetCurrentState(TileUtility::ETileState::IDLE);
	GameBoard[Row][Col] = MoveTemp(NewTile);
	return *GameBoard[Row][Col];
}

TIG::TileID TIGLogicalBoard::GetTileAtCoordinate(BoardUtility::TileCoordinate Coordinate) const
{
	check(IsValidCoordinate(Coordinate) && "GetTileAtCoordinate: Invalid Coordinate Specified");

	return GameBoard[Coordinate.Row][Coordinate.Col]->GetUniqueID();
}

const TIGLogicalTile& TIGLogicalBoard::GetTileForID(TIG::TileID TileID) const
{
	check(TileIDToTile.Contains(TileID) && "GetTileForID - Requesting an ID not in the map");
	return *(*TileIDToTile.Find(TileID));
}
