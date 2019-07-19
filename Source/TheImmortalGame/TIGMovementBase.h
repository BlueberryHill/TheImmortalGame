// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class TIGMove;
class TIGLogicalArena;

/**
 * 
 */
class THEIMMORTALGAME_API TIGMovementBase
{
public:
	TIGMovementBase();
	~TIGMovementBase();

	virtual void CalculateAllMoves(const TIGLogicalArena& Arena, TArray<Move>& Moves) = 0;
};
