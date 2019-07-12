// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGLogicalArena.h"

#include "Board/BoardUtility.h"
#include "Board/TIGLogicalBoard.h"
#include "Board/TIGLogicalTile.h"

#include "General/LogicalTypes.h"

#include "Database/TIGStartingPieces.h"

TIGLogicalArena::TIGLogicalArena()
{
}

TIGLogicalArena::~TIGLogicalArena()
{
}

const TIGLogicalPiece & TIGLogicalArena::GetPieceForID(int32 PieceID) const
{
	return PieceManager.GetPieceForID(PieceID);
}

void TIGLogicalArena::Init(const BoardUtility::BoardDimensions & Dimensions, const UDataTable& StartingPieceLayout)
{
	InitGameBoard(Dimensions);
	InitPieceManager(StartingPieceLayout);
}

int32 TIGLogicalArena::GetTileAtCoordinate(BoardUtility::TileCoordinate BoardCoordinate) const
{
	return GameBoard->GetTileAtCoordinate(BoardCoordinate);
}

//#TODO: Make data driven
void TIGLogicalArena::InitGameBoard(BoardUtility::BoardDimensions Dimensions)
{
	GameBoard = MakeUnique<TIGLogicalBoard>(Dimensions);
	Delegates.BoardCreated.Broadcast(GameBoard->GetNumRows(), GameBoard->GetNumCols());

	for (int32 Row = 0; Row < GameBoard->GetNumRows(); ++Row)
	{
		for (int32 Col = 0; Col < GameBoard->GetNumCols(); ++Col)
		{
			const TIGLogicalTile& NewTile = GameBoard->AddTile(Row, Col);
			Delegates.TileSpawned.Broadcast(Row, Col, NewTile.GetUniqueID());
		}
	}
}

void TIGLogicalArena::InitPieceManager(const UDataTable& StartingPieceLayout)
{
		int32 FakeUniqueID = 1; //#TODO: Remove when add multiple players
		for (auto& KeyRowPair : StartingPieceLayout.GetRowMap())
		{
			FTIGStartingPieces* PieceRow = (FTIGStartingPieces*)(KeyRowPair.Value); //#TODO: Safer to get all names then extract rows from names
			if (PieceRow->Col >= 0)
			{
				AddPiece(PieceRow->Row, PieceRow->Col, PieceRow->PieceType, FakeUniqueID);
			}
			else
			{
				AddRowOfPieces(PieceRow->Row, PieceRow->PieceType, FakeUniqueID);
			}
		}
}

void TIGLogicalArena::AddRowOfPieces(const int32 Row, const EPieceType PieceType, TIG::PlayerID OwningPlayerID)
{
	check(GameBoard != nullptr && "TIGArena - No GameBoard");

	for (int32 Col = 0; Col < GameBoard->GetNumCols(); ++Col)
	{
		AddPiece(Row, Col, PieceType, OwningPlayerID);
	}
}

void TIGLogicalArena::AddPiece(const int32 Row, const int32 Col, const EPieceType PieceType, TIG::PlayerID OwningPlayerID)
{
	TIG::PieceID NewPieceID = PieceManager.CreatePiece(OwningPlayerID, PieceType); 
	TIG::TileID  TileID = GetTileAtCoordinate({ Row, Col });
	TilePieceAssociation.PieceSpawned(NewPieceID, TileID);
	
	Delegates.PieceSpawned.Broadcast(Row, Col, NewPieceID);

	check(TileID != TIG::INVALID_TILE_ID && "TIGLogicalArena::AddPiece - Trying to create piece but no tile"); 

}

void TIGLogicalArena::TilePieceBiMap::PieceSpawned(TIG::PieceID PieceID, TIG::TileID TileID)
{
	PieceToTile.Emplace(PieceID, TileID);
	TileToPiece.Emplace(TileID, PieceID);
}

TIG::PieceID TIGLogicalArena::TilePieceBiMap::GetPieceOnTile(TIG::TileID TileID) const
{
	const int32* PieceID = TileToPiece.Find(TileID);
	return PieceID ? *PieceID : TIG::INVALID_PIECE_ID;
}

TIG::TileID TIGLogicalArena::TilePieceBiMap::GeTileForPiece(TIG::TileID PieceID) const
{
	const int32* TileID = PieceToTile.Find(PieceID);
	return TileID ? *TileID : TIG::INVALID_TILE_ID;
}
