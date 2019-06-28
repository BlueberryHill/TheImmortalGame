// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "Pieces/PieceUtility.h"

#include "TIGStartingPieces.generated.h"

/**
 * 
 */


USTRUCT(Blueprintable)
struct THEIMMORTALGAME_API FTIGStartingPieces : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Row = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Col = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EPieceType PieceType = EPieceType::NUM;

};
