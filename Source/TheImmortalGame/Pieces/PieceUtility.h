// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "PieceUtility.generated.h"

UENUM(BlueprintType)
enum class EPieceType : uint8
{
	PAWN    UMETA(DisplayName = "Pawn"),
	ROOK    UMETA(DisplayName = "Rook"),
	KNIGHT  UMETA(DisplayName = "Knight"),
	BISHOP  UMETA(DisplayName = "Bishop"),
	QUEEN   UMETA(DisplayName = "Queen"),
	KING    UMETA(DisplayName = "King"),

	NUM     UMETA(DisplayName = "Invalid")
};
