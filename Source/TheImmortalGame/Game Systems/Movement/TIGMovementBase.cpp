// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGMovementBase.h"

TIGMovementBase::TIGMovementBase(MovementUtility::FMovementRules&& Rules, MovementUtility::EDirection Facing) :
	MovementRules(MoveTemp(Rules))
{
	UpdateMoves(Facing);
}

TIGMovementBase::~TIGMovementBase()
{
}

void TIGMovementBase::UpdateMoves(MovementUtility::EDirection Facing)
{
	CurrentAvailableMoves = MovementUtility::GetAvailableMovement(MovementRules, Facing);
}
