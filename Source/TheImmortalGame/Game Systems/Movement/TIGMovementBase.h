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
	TIGMovementBase();
	~TIGMovementBase();

protected:
	MovementUtility::LinearMovementArray LinearMovement;
};
