// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "General/LogicalTypes.h"

#include "PieceUtility.h"
#include "TIGPieceManager.generated.h"
/**
 * 
 */

class UMaterial;
class UMaterialInstanceDynamic;

class ATIGPlayerState;
class ATIGPiece;

UCLASS(Blueprintable)
class THEIMMORTALGAME_API UTIGPieceManager : public UObject
{
	GENERATED_BODY()
public:
	using Army	   = TArray<ATIGPiece*>;
	using PlayerID = TIG::PlayerID;
	using PieceID  = TIG::PieceID;

	using PlayerIDToArmy = TMap<PlayerID, Army>;
	using PieceToID = TMap<ATIGPiece*, PieceID>;

public:
	UTIGPieceManager();
	~UTIGPieceManager();

	ATIGPiece* CreatePiece(const ATIGPlayerState& Player, EPieceType Type, PieceID ID, const FTransform& Transform); 
	PieceID	   GetPieceID(const ATIGPiece& Piece) const;

	void	   OnPieceSelected(ATIGPiece& Piece);
	void	   OnPieceDeselected(ATIGPiece& Piece);

	void	   Init();

private:
	PlayerIDToArmy PlayerPieces;
	PieceToID	   ActivePieces;

	UPROPERTY(EditDefaultsOnly, Category = "Piece Types")
	TSubclassOf<ATIGPiece> PieceClass[static_cast<uint8>(EPieceType::NUM)];

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	UMaterial* BaseMaterial;
};
