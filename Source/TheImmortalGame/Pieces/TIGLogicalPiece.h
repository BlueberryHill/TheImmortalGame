// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "General/LogicalTypes.h"
#include "Game Systems/Movement/MovementUtility.h"

enum class EPieceType : uint8;

class TIGMovementBase;
/**
 * 
 */
class THEIMMORTALGAME_API TIGLogicalPiece
{
public:
	TIGLogicalPiece(EPieceType Type);
	~TIGLogicalPiece();

	TIG::PieceID  GetUniqueID() const { return UniqueID; }
	EPieceType	  GetType()     const { return BaseType; }

	MovementUtility::EDirection GetFacingDirection() { return Facing; }
private:
	TIG::PieceID	 UniqueID;
	EPieceType		 BaseType;

	MovementUtility::EDirection Facing;
};
