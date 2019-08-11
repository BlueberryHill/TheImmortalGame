// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TIGMovementBase.h"

/**
 * 
 */
class THEIMMORTALGAME_API TIGPawnMovement : public TIGMovementBase
{
public:
	TIGPawnMovement(MovementUtility::FMovementRules&&, MovementUtility::EDirection Facing);
	~TIGPawnMovement();
};
