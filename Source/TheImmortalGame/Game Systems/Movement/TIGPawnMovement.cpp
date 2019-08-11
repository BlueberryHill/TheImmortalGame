// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGPawnMovement.h"




TIGPawnMovement::TIGPawnMovement(MovementUtility::FMovementRules&& Rules, MovementUtility::EDirection Facing) 
	: TIGMovementBase(MoveTemp(Rules), Facing)
{
}

TIGPawnMovement::~TIGPawnMovement()
{
}

