// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EPieceType : uint8;

namespace MovementUtility
{
	enum class EDirection : uint8
	{
		 NORTH
		,SOUTH
		,EAST
		,WEST
		,NORTH_EAST
		,NORTH_WEST
		,SOUTH_EAST
		,SOUTH_WEST
		,NUM
	};

	enum class EMovementType : uint8
	{
		 SLIDE
		,JUMP
		,NUM
	};

	const int32 UNLIMITED_RANGE = -1;
	const int32 DEFAULT_PAWN_INITIAL_RANGE = 2;

	struct FLinearMovement
	{
		EDirection		Direction = EDirection::NUM;
		EMovementType   Type	  = EMovementType::NUM;
		int32			Range	  = UNLIMITED_RANGE;
	};

	using LinearMovementArray = MovementUtility::FLinearMovement[static_cast<uint8>(MovementUtility::EDirection::NUM)];

	struct FLinearMovements
	{
		LinearMovementArray LinearMovements;
	};


	FLinearMovements DefaultMovementForBaseType(EDirection Facing, EPieceType Type);
}