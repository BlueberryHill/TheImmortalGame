// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "General/EnumUtil.h"

#include <limits>

enum class EPieceType : uint8;

namespace BoardUtility
{
	struct TileCoordinate;
}

namespace MovementUtility
{
	enum class EDirection : uint8
	{
		  NORTH = 0
		, SOUTH
		, EAST
		, WEST
		, NORTH_WEST
		, NORTH_EAST
		, SOUTH_WEST
		, SOUTH_EAST
		, NUM
	};

	enum class ERelativeDirection : uint8
	{
		 FORWARD = 0
		,BACKWARD
		,LEFT
		,RIGHT
		,DIAGONAL_LEFT
		,DIAGONAL_RIGHT
		,REVERSE_DIAGONAL_LEFT
		,REVERSE_DIAGONAL_RIGHT
		,NUM
	};

	enum class EMovementType : uint8
	{
		 SLIDE
		,JUMP
		,NUM
	};

	void IncrementCoordinate(BoardUtility::TileCoordinate& Coordinate, EDirection Direction);

	const int32 UNLIMITED_RANGE = std::numeric_limits<int32>::max();
	const int32 DEFAULT_PAWN_INITIAL_RANGE = 2;
	const int32 DEFAULT_KING_INITIAL_RANGE = 1;
	const int32	NO_MOVEMENT = 0;

	template<typename DirectionEnum>
	struct FLinearMovement
	{
		DirectionEnum Direction = DirectionEnum::NUM;
		EMovementType Type		= EMovementType::NUM;
		int32		  Range		= NO_MOVEMENT;
	};

	using LinearMovementRuleArray	= FLinearMovement<ERelativeDirection>[TIG::enum_to_value(ERelativeDirection::NUM)];
	using LinearMovementArray		= FLinearMovement<EDirection>[TIG::enum_to_value(EDirection::NUM)];

	struct FLinearMovements
	{
		LinearMovementArray MoveArray;
	};

	struct FLinearMovementRules
	{
		LinearMovementRuleArray RuleArray;
	};

	struct FMovement
	{
		FLinearMovements LinearMovements;
	};

	struct FMovementRules
	{
		FLinearMovementRules LinearMovements;
	};

	FMovementRules GetDefaultMovementRules(EPieceType Type);
	FMovement	   GetAvailableMovement(const FMovementRules& Rules, EDirection FacingDirection);

}