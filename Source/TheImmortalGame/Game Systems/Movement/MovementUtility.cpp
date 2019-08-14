// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementUtility.h"
#include "Board/BoardUtility.h"

#include "Pieces/PieceUtility.h"

#include "General/EnumUtil.h"


namespace MovementUtility
{
	struct FAbsoluteDirections
	{
		EDirection AbsoluteDirections[TIG::enum_to_value(ERelativeDirection::NUM)];
	};

	struct FRelativeToAbsoluteDirection
	{
		TMap<EDirection, FAbsoluteDirections> DirectionMap;
	};


	void SetMovement(ERelativeDirection Direction, FLinearMovement<ERelativeDirection>&& Movement, LinearMovementRuleArray& Movements)
	{
		Movements[TIG::enum_to_value(Direction)] = std::move(Movement);
	}


	// TODO: Break rules into separate file

	FLinearMovementRules DefaultPawnRules() //#TODO: Could make this data driven
	{
		FLinearMovementRules DefaultPawnMovement;
		SetMovement(ERelativeDirection::FORWARD, { ERelativeDirection::FORWARD, EMovementType::SLIDE, DEFAULT_PAWN_INITIAL_RANGE }, DefaultPawnMovement.RuleArray);

		return DefaultPawnMovement;
	}

	FLinearMovementRules DefaultRookRules() 
	{
		FLinearMovementRules DefaultRookMovement;
		SetMovement(ERelativeDirection::FORWARD, { ERelativeDirection::FORWARD, EMovementType::SLIDE, UNLIMITED_RANGE }, DefaultRookMovement.RuleArray);
		SetMovement(ERelativeDirection::BACKWARD, { ERelativeDirection::BACKWARD, EMovementType::SLIDE, UNLIMITED_RANGE }, DefaultRookMovement.RuleArray);
		SetMovement(ERelativeDirection::LEFT, { ERelativeDirection::LEFT, EMovementType::SLIDE, UNLIMITED_RANGE }, DefaultRookMovement.RuleArray);
		SetMovement(ERelativeDirection::RIGHT, { ERelativeDirection::RIGHT, EMovementType::SLIDE, UNLIMITED_RANGE }, DefaultRookMovement.RuleArray);

		return DefaultRookMovement;
	}

	FLinearMovementRules DefaultBishopRules()
	{
		FLinearMovementRules DefaultBishopMovement;
		SetMovement(ERelativeDirection::DIAGONAL_RIGHT, { ERelativeDirection::DIAGONAL_RIGHT, EMovementType::SLIDE, UNLIMITED_RANGE }, DefaultBishopMovement.RuleArray);
		SetMovement(ERelativeDirection::REVERSE_DIAGONAL_RIGHT, { ERelativeDirection::REVERSE_DIAGONAL_RIGHT, EMovementType::SLIDE, UNLIMITED_RANGE }, DefaultBishopMovement.RuleArray);
		SetMovement(ERelativeDirection::DIAGONAL_LEFT, { ERelativeDirection::DIAGONAL_LEFT, EMovementType::SLIDE, UNLIMITED_RANGE }, DefaultBishopMovement.RuleArray);
		SetMovement(ERelativeDirection::REVERSE_DIAGONAL_LEFT, { ERelativeDirection::REVERSE_DIAGONAL_LEFT, EMovementType::SLIDE, UNLIMITED_RANGE }, DefaultBishopMovement.RuleArray);

		return DefaultBishopMovement;
	}



	FLinearMovementRules GetDefaultLinearRules(EPieceType Type)
	{
		switch (Type)
		{
		case EPieceType::PAWN:
			return DefaultPawnRules();
		case EPieceType::ROOK:
			return DefaultRookRules();
		case EPieceType::KNIGHT:
			return DefaultRookRules();
		case EPieceType::BISHOP:
			return DefaultBishopRules();
		case EPieceType::QUEEN:
			return DefaultRookRules();
		case EPieceType::KING:
			return DefaultRookRules();
		default:
			checkNoEntry();
			return DefaultPawnRules();
		}

	}

	const FRelativeToAbsoluteDirection& RelativeToAbsoluteDirections()
	{
		using namespace TIG;
		auto CreateDirectionMapping = []()
		{
			FRelativeToAbsoluteDirection RelativeToAbsoluteDirection;
			FAbsoluteDirections NorthFacing;
			NorthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::FORWARD)]				  = EDirection::NORTH;
			NorthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::BACKWARD)]				  = EDirection::SOUTH;
			NorthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::LEFT)]					  = EDirection::WEST;
			NorthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::RIGHT)]				  = EDirection::EAST;
			NorthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::REVERSE_DIAGONAL_RIGHT)] = EDirection::SOUTH_EAST;
			NorthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::REVERSE_DIAGONAL_LEFT)]  = EDirection::SOUTH_WEST;
			NorthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::DIAGONAL_LEFT)]		  = EDirection::NORTH_WEST;
			NorthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::DIAGONAL_RIGHT)]		  = EDirection::NORTH_EAST;


			FAbsoluteDirections SouthFacing;
			SouthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::FORWARD)]				   = EDirection::SOUTH;
			SouthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::BACKWARD)]				   = EDirection::NORTH;
			SouthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::LEFT)]					   = EDirection::EAST;
			SouthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::RIGHT)]				   = EDirection::WEST;
			SouthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::REVERSE_DIAGONAL_RIGHT)]  = EDirection::NORTH_WEST;
			SouthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::REVERSE_DIAGONAL_LEFT)]   = EDirection::NORTH_EAST;
			SouthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::DIAGONAL_LEFT)]		   = EDirection::SOUTH_EAST;
			SouthFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::DIAGONAL_RIGHT)]		   = EDirection::SOUTH_WEST;

			FAbsoluteDirections EastFacing;
			EastFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::FORWARD)]				  = EDirection::EAST;
			EastFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::BACKWARD)]				  = EDirection::WEST;
			EastFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::LEFT)]					  = EDirection::NORTH;
			EastFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::RIGHT)]				      = EDirection::SOUTH;
			EastFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::REVERSE_DIAGONAL_RIGHT)]  = EDirection::SOUTH_WEST;
			EastFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::REVERSE_DIAGONAL_LEFT)]   = EDirection::SOUTH_EAST;
			EastFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::DIAGONAL_LEFT)]		      = EDirection::NORTH_EAST;
			EastFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::DIAGONAL_RIGHT)]		  = EDirection::NORTH_WEST;

			FAbsoluteDirections WestFacing;
			WestFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::FORWARD)]				  = EDirection::WEST;
			WestFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::BACKWARD)]				  = EDirection::EAST;
			WestFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::LEFT)]					  = EDirection::SOUTH;
			WestFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::RIGHT)]				      = EDirection::NORTH;
			WestFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::REVERSE_DIAGONAL_RIGHT)]  = EDirection::NORTH_EAST;
			WestFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::REVERSE_DIAGONAL_LEFT)]   = EDirection::SOUTH_EAST;
			WestFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::DIAGONAL_LEFT)]		      = EDirection::SOUTH_WEST;
			WestFacing.AbsoluteDirections[enum_to_value(ERelativeDirection::DIAGONAL_RIGHT)]		  = EDirection::NORTH_WEST;

			RelativeToAbsoluteDirection.DirectionMap.Emplace(EDirection::NORTH, NorthFacing);
			RelativeToAbsoluteDirection.DirectionMap.Emplace(EDirection::SOUTH, SouthFacing);
			RelativeToAbsoluteDirection.DirectionMap.Emplace(EDirection::EAST , EastFacing );
			RelativeToAbsoluteDirection.DirectionMap.Emplace(EDirection::WEST , WestFacing );

			return RelativeToAbsoluteDirection;
		};

		static const FRelativeToAbsoluteDirection DirectionMapping = CreateDirectionMapping();
		return DirectionMapping;
	}

	void IncrementCoordinate(BoardUtility::TileCoordinate& Coordinate, EDirection Direction)
	{
		switch (Direction)
		{
			case EDirection::NORTH:
			{
				++Coordinate.Row;
				break;
			}
			case EDirection::SOUTH:
			{
				--Coordinate.Row;
				break;
			}
			case EDirection::EAST:
			{
				++Coordinate.Col;
				break;
			}
			case EDirection::WEST:
			{
				--Coordinate.Col;
				break;
			}
			case EDirection::NORTH_EAST:
			{
				++Coordinate.Col;
				++Coordinate.Row;
				break;
			}
			case EDirection::NORTH_WEST:
			{
				++Coordinate.Row;
				--Coordinate.Col;
				break;
			}
			case EDirection::SOUTH_EAST:
			{
				--Coordinate.Row;
				++Coordinate.Col;
				break;
			}
			case EDirection::SOUTH_WEST:
			{
				--Coordinate.Row;
				--Coordinate.Col;
				break;
			}
			default:
				checkNoEntry();
		}
	}

	FMovementRules GetDefaultMovementRules(EPieceType Type)
	{
		FMovementRules Movement; 
		Movement.LinearMovements = GetDefaultLinearRules(Type);
		return Movement;
	}
	FMovement GetAvailableMovement(const FMovementRules& Rules, EDirection FacingDirection)
	{
		check(TIG::enum_to_value(EDirection::NUM) == TIG::enum_to_value(ERelativeDirection::NUM) && "GetAvailableMovement() : Absolute and relative directions are out of sync.");

		const FRelativeToAbsoluteDirection& RelativeToAbsoluteDirection = RelativeToAbsoluteDirections();
		check(RelativeToAbsoluteDirection.DirectionMap.Contains(FacingDirection) && "GetAvailableMovement() : No direction mapping for requested facing direction");


		FMovement AvailableMovement;
		const FAbsoluteDirections& AbsoluteDirections = *RelativeToAbsoluteDirection.DirectionMap.Find(FacingDirection); 

		for (uint8 DirectionIdx = 0; DirectionIdx < TIG::enum_to_value(ERelativeDirection::NUM); ++DirectionIdx) 
		{
			FLinearMovement<ERelativeDirection> Rule = Rules.LinearMovements.RuleArray[DirectionIdx];
			EDirection AbsoluteDirection = AbsoluteDirections.AbsoluteDirections[TIG::enum_to_value(Rule.Direction)];
			AvailableMovement.LinearMovements.MoveArray[DirectionIdx] = { AbsoluteDirection, Rule.Type, Rule.Range };
		}

		return AvailableMovement;

	}
}
