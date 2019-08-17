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

	TIG::TileID FromTile = Arena.GetTileForPiece(PieceID);
	check(FromTile != TIG::INVALID_TILE_ID && "Requesting movement for piece without a position");

	FMovement PotentialMovement = PieceMovement.GetAvailableMoves();

	for (const FLinearMovement<EDirection>& Movement : PotentialMovement.LinearMovements.MoveArray)
	{
		if (Movement.Range == NO_MOVEMENT)
		{
			continue;
		}

		TArray<TIG::TileID> MoveResult;
		if (Movement.Type == EMovementType::SLIDE)
		{
			Arena.GetNextNFreeTiles(FromTile, Movement.Direction, Movement.Range, MoveResult);
		}
		else if (Movement.Type == EMovementType::JUMP)
		{
			TIG::TileID ID = Arena.GetTileInDirection(FromTile, Movement.Direction, Movement.Range);
			if (ID != TIG::INVALID_TILE_ID)
			{
				MoveResult.Add(ID);
			}
		}


		//TODO: Implement Captures

		ReachableTiles.Append(MoveResult);
	}

	//TODO: Refactor New function

	for (const FSequenceMovement<EDirection>& SequenceMovement : PotentialMovement.SequenceMovements)
	{
		TIG::TileID TileIDInSequence = FromTile;
		for (const FLinearMovement<EDirection>& Movement : SequenceMovement.Movements)
		{
			check(Movement.Type == EMovementType::JUMP && "Only jump is currently supported for sequence movements");
			if (Movement.Range == NO_MOVEMENT)
			{
				continue;
			}
			
			TileIDInSequence = Arena.GetTileInDirection(TileIDInSequence, Movement.Direction, Movement.Range);
			if (TileIDInSequence == TIG::INVALID_TILE_ID)
			{
				break;
			}
		}

		if (TileIDInSequence != TIG::INVALID_TILE_ID && Arena.TileIsOccupied(TileIDInSequence) == false)
		{
			ReachableTiles.Add(TileIDInSequence);
		}

	}

	//TODO: Implement Captures
	
	return ReachableTiles;
}

void TIGMovementManager::AddPiece(TIG::TileID ID, EPieceType PieceType)
{
	PieceMovementMap.Emplace(ID, MakeUnique<TIGMovementBase>(MovementUtility::GetDefaultMovementRules(PieceType), MovementUtility::EDirection::NORTH));
}
