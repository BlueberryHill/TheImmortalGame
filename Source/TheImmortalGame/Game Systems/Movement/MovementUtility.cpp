// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementUtility.h"

#include "Pieces/PieceUtility.h"


namespace MovementUtility
{
	void SetMovement(EDirection Direction, FLinearMovement&& Movement, LinearMovementArray& Movements)
	{
		Movements[static_cast<uint8>(Direction)] = std::move(Movement);
	}

	FLinearMovements DefaultMovementForPawn(EDirection Facing)
	{
		FLinearMovements DefaultPawnMovement;
		SetMovement(Facing, { Facing, EMovementType::SLIDE, DEFAULT_PAWN_INITIAL_RANGE }, DefaultPawnMovement.LinearMovements);

		return DefaultPawnMovement;
	}


	FLinearMovements DefaultMovementForBaseType(EDirection Facing, EPieceType Type)
	{
		Type;
		return DefaultMovementForPawn(Facing);
	}
}
