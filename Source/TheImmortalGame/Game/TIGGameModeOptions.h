// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Board/TIGGridBoard.h"
#include "Pieces/TIGPieceManager.h"

#include "TIGGameModeOptions.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class THEIMMORTALGAME_API UTIGGameModeOptions : public UObject
{
	GENERATED_BODY()
public:
	UTIGGameModeOptions();
	~UTIGGameModeOptions();

public:
	const TSubclassOf<ATIGGridBoard>& GetBoardClass() const { return BoardClass; }
	const TSubclassOf<UTIGPieceManager>& GetPieceManagerClass() const { return PieceManagerClass; }
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Board")
	TSubclassOf<ATIGGridBoard> BoardClass;

	UPROPERTY(EditDefaultsOnly, Category = "Pieces")
	TSubclassOf<UTIGPieceManager> PieceManagerClass;

};
