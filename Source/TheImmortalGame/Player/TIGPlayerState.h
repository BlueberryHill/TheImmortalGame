// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TIGPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class THEIMMORTALGAME_API ATIGPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ATIGPlayerState();

	int32 GetUniqueID() const { return UniqueID; }

private:
	int32 UniqueID = 0;
};
