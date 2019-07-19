// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "General/LogicalTypes.h"

/**
 * 
 */

class TIGLogicalArena;

class THEIMMORTALGAME_API TIGMovementManager
{
public:
	TIGMovementManager();
	~TIGMovementManager();

	TArray<TIG::TileID> CalculatePossibleMovesForPiece(TIG::PieceID, const TIGLogicalArena& Arena);



};
