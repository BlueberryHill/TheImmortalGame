// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGLogicalBoard.h"

#include "TIGLogicalTile.h"

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

TIGLogicalBoard::~TIGLogicalBoard()
{
}

const TIGLogicalTile& TIGLogicalBoard::AddTile(int32 Row, int32 Col)
{
	check(GameBoard[Row][Col] && GameBoard[Row][Col]->GetUniqueID() == -1 && "AddTile() - Board has not been initialised correctly");
	GameBoard[Row][Col] = MakeUnique<Tile>();
	return *GameBoard[Row][Col];
}

TIG::TileID TIGLogicalBoard::GetTileAtCoordinate(BoardUtility::TileCoordinate Coordinate)
{
	check(Coordinate.Row < GetNumRows() && Coordinate.Row >= 0 && "GetTileAtCoordinate: Invalid Row Specified");
	check(Coordinate.Col < GetNumCols() && Coordinate.Col >= 0 && "GetTileAtCoordinate: Invalid Row Specified");

	return GameBoard[Coordinate.Row][Coordinate.Col]->GetUniqueID();
}
