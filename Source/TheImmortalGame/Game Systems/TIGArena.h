// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TIGArena.generated.h"

class UTIGPieceManager;
class ATIGGridBoard;
class ATIGPlayerState;

class UDataTable;

enum class EPieceType : uint8;
/**
 * 
 */
UCLASS(Blueprintable)
class THEIMMORTALGAME_API UTIGArena : public UObject
{
	GENERATED_BODY()
public:
	UTIGArena();
	~UTIGArena();

	void InitArena(UTIGPieceManager& PieceManager, ATIGGridBoard& GameBoard);

	void PrepareToStart();


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Pieces")
	UDataTable* StartingPieces;
private:
	UTIGPieceManager* PieceManager = nullptr; 
	ATIGGridBoard* GameBoard = nullptr;

	void AddRowOfPieces(const int32 Row, const EPieceType PieceType, ATIGPlayerState& OwningPlayer);
	void AddPiece(const int32 Row, const int32 Col, const EPieceType PieceType, ATIGPlayerState& OwningPlayer);

};
