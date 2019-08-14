// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGMovementManager.h"

#include "MovementUtility.h"
#include "TIGMovementBase.h"

#include "../TIGLogicalArena.h"

#include "Pieces/TIGLogicalPiece.h"
#include "Pieces/PieceUtility.h"

#include "General/EnumUtil.h"



TIGMovementManager::TIGMovementManager()
{
}

TIGMovementManager::~TIGMovementManager()
{
}

TArray<TIG::TileID> TIGMovementManager::CalculatePossibleMovesForPiece(TIG::PieceID PieceID, const TIGLogicalArena& Arena) const
{
	using namespace MovementUtility;

	TArray<TIG::TileID> ReachableTiles;

	check(PieceMovementMap.Contains(PieceID) && "CalculatePossibleMovesForPiece() - PieceID missing from map");
	const TIGMovementBase& PieceMovement = **PieceMovementMap.Find(PieceID);

	FMovement PotentialMovement = PieceMovement.GetAvailableMoves();

	for (FLinearMovement<EDirection> Movement : PotentialMovement.LinearMovements.MoveArray)
	{
		if (Movement.Range == NO_MOVEMENT)
		{
			continue;
		}

		TIG::TileID FromTile = Arena.GetTileForPiece(PieceID);
		check(FromTile != TIG::INVALID_TILE_ID && "Requesting movement for piece without a position");


		TArray<TIG::TileID> MoveResult;
		if (Movement.Type == EMovementType::SLIDE)
		{
			Arena.GetNextNFreeTiles(FromTile, Movement.Direction, Movement.Range, MoveResult);
		}
		else if (Movement.Type == EMovementType::JUMP)
		{
			//TODO: Implement
		}

		//TODO: Implement Captures

		ReachableTiles.Append(MoveResult);
	}

	return ReachableTiles;
}

void TIGMovementManager::AddPiece(TIG::TileID ID, EPieceType PieceType)
{
	PieceMovementMap.Emplace(ID, MakeUnique<TIGMovementBase>(MovementUtility::GetDefaultMovementRules(PieceType), MovementUtility::EDirection::NORTH));
}
