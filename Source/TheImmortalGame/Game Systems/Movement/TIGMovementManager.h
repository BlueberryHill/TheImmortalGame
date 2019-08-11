// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "General/LogicalTypes.h"

/**
 * 
 */

class TIGLogicalArena;
class TIGMovementBase;

class THEIMMORTALGAME_API TIGMovementManager
{
	using MovementPtr = TUniquePtr<TIGMovementBase>;
public:
	TIGMovementManager();
	~TIGMovementManager();

	TIGMovementManager(const TIGMovementManager&) = delete;
	TIGMovementManager(TIGMovementManager&&) = delete;
	TIGMovementManager& operator=(const TIGMovementManager&) = delete;
	TIGMovementManager& operator=(const TIGMovementManager&&) = delete;

	TArray<TIG::TileID> CalculatePossibleMovesForPiece(TIG::PieceID, const TIGLogicalArena& Arena) const;
	void				AddPiece(TIG::TileID ID);

private:
	TMap<TIG::PieceID, MovementPtr> PieceMovementMap;
};
