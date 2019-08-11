// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementUtility.h"
/**
 * 
 */ 

class THEIMMORTALGAME_API TIGMovementBase
{
public:
	TIGMovementBase(MovementUtility::FMovementRules&&, MovementUtility::EDirection Facing);
	~TIGMovementBase();

	const MovementUtility::FMovement& GetAvailableMoves() const { return CurrentAvailableMoves; }
protected:
	void UpdateMoves(MovementUtility::EDirection Facing);

	MovementUtility::FMovement		CurrentAvailableMoves;
	MovementUtility::FMovementRules MovementRules;

};
