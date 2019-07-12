// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TIGArena.generated.h"

class UTIGPieceManager;
class ATIGGridBoard;
class ATIGPlayerState;

class TIGLogicalArena;

class UDataTable;

struct  FArenaDelegates;

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

	void InitArena(TIGLogicalArena& Arena);
private:
	UFUNCTION()
	void BoardCreated(int32 NumRows, int32 NumCols); 

	UFUNCTION()
	void PieceCreated(int32 Row, int32 Col, int32 PieceID);

	UFUNCTION()
	void TileCreated(int32 Row, int32 Col, int32 TileID);

	UTIGPieceManager* PieceManager = nullptr; 
	ATIGGridBoard* GameBoard = nullptr;

	const TIGLogicalArena* LogicalArena = nullptr;

	void AddRowOfPieces(int32 Row, EPieceType PieceType, const ATIGPlayerState& OwningPlayer);
	void AddPiece(int32 Row, int32 Col, EPieceType PieceType, const ATIGPlayerState& OwningPlayer);

	void SetupDelegates(TIGLogicalArena& Arena);
};
