// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGLogicalArena.h"

#include "Board/BoardUtility.h"
#include "Board/TIGLogicalBoard.h"
#include "Board/TIGLogicalTile.h"

#include "Database/TIGStartingPieces.h"

TIGLogicalArena::TIGLogicalArena()
{
}

TIGLogicalArena::~TIGLogicalArena()
{
}

const TIGLogicalPiece & TIGLogicalArena::GetPieceForID(TIG::PieceID PieceID) const
{
	return PieceManager.GetPieceForID(PieceID);
}

const TIGLogicalTile & TIGLogicalArena::GetTileForID(TIG::TileID TileID) const
{
	return GameBoard->GetTileForID(TileID);
}

void TIGLogicalArena::Init(const BoardUtility::BoardDimensions & Dimensions, const UDataTable& StartingPieceLayout)
{
	InitGameBoard(Dimensions);
	InitPieceManager(StartingPieceLayout);
}

TArray<TIG::TileID> TIGLogicalArena::GetFreeTilesToMoveTo(TIG::PieceID ID) const
{
	return MovementManager.CalculatePossibleMovesForPiece(ID, *this);
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

	MovementManager.AddPiece(NewPieceID);
	
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

void TIGLogicalArena::GetNextNFreeTiles(TIG::TileID From, MovementUtility::EDirection Direction, int32 N, TArray<TIG::TileID>& OutTileArray) const
{
	GameBoard->GetNextNTiles(From, Direction, N, OutTileArray);
	RemoveBlockedTiles(OutTileArray);
	
}

void  TIGLogicalArena::RemoveBlockedTiles(TArray<TIG::TileID>& OutTileArray) const
{
	auto TileIsOccupied = [this](const TIG::TileID ID) -> bool
	{
		return GetPieceForTile(ID) != TIG::INVALID_PIECE_ID;
	};

	TIG::TileID* FirstOccupiedTile = OutTileArray.FindByPredicate(TileIsOccupied);
	if (FirstOccupiedTile != nullptr)
	{
		int32 BlockedIndex = OutTileArray.Find(*FirstOccupiedTile);
		int32 NumTilesRemaining = BlockedIndex - 1;
		check(NumTilesRemaining > 0 && "GetNextNFreeTiles - Invalid Blocked Index");
		OutTileArray.SetNumZeroed(NumTilesRemaining);
	}
}

TileUtility::ETileState TIGLogicalArena::GetTileState(TIG::TileID ID) const
{
	const TIGLogicalTile& Tile = GameBoard->GetTileForID(ID);
	return Tile.CurrentState();
}

TIG::PieceID TIGLogicalArena::GetTileForPiece(TIG::PieceID PieceID) const
{
	return TilePieceAssociation.GetTileForPiece(PieceID);
}

TIG::PieceID TIGLogicalArena::GetPieceForTile(TIG::TileID TileID) const
{
	return TilePieceAssociation.GetPieceOnTile(TileID);
}

TIG::TileID TIGLogicalArena::TilePieceBiMap::GetTileForPiece(TIG::TileID PieceID) const
{
	const int32* TileID = PieceToTile.Find(PieceID);
	return TileID ? *TileID : TIG::INVALID_TILE_ID;
}
