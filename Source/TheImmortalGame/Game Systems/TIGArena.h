// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "General/LogicalTypes.h"

#include "CoreMinimal.h"
#include "TIGArena.generated.h"

class UTIGPieceManager;
class ATIGGridBoard;
class ATIGPlayerState;
class ATIGPiece;
class ATIGTile;

class TIGLogicalArena;

class UDataTable;

struct  FTIGArenaDelegates;

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

	void InitArena(const TIGLogicalArena& Arena, FTIGArenaDelegates& Delegates);

	TIG::PieceID GetPieceID(const ATIGPiece& Piece) const;
	TIG::TileID  GetTileID(const ATIGTile& Tile) const;
	void		 OnPieceSelected(ATIGPiece& Piece);
	void HighlightPotentialMovementTiles(ATIGPiece & Piece);
	void		 OnPieceDeselected(ATIGPiece& Piece);
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

	TArray<TIG::TileID> HighlightedTiles;

	void AddPiece(int32 Row, int32 Col, EPieceType PieceType, TIG::PieceID, const ATIGPlayerState& OwningPlayer);

	void SetupDelegates(FTIGArenaDelegates& Delegates);

	void UnHighlightAllTiles();
};
