// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TIGArena.generated.h"

class UTIGPieceManager;
class ATIGGridBoard;

/**
 * 
 */
UCLASS()
class THEIMMORTALGAME_API UTIGArena : public UObject
{
	GENERATED_BODY()
public:
	UTIGArena();
	~UTIGArena();

	void InitArena(UTIGPieceManager& PieceManager, ATIGGridBoard& GameBoard);

	void PrepareToStart();

private:
	UTIGPieceManager* PieceManager = nullptr; 
	ATIGGridBoard* GameBoard = nullptr;
};
