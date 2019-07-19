// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "General/LogicalTypes.h"
/**
 * 
 */

struct FSubMove
{
	TIG::TileID  From;
	TIG::TileID  To;
	TIG::PieceID Piece;
};

class THEIMMORTALGAME_API TIGMove
{
public:
	TIGMove();
	~TIGMove();

private:
	TArray<FSubMove> Move;
};
