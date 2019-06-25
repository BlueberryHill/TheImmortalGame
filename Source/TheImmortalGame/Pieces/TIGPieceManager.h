// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "PieceUtility.h"
#include "TIGPieceManager.generated.h"
/**
 * 
 */

class ATIGPlayerState;
class ATIGPiece;

UCLASS(Blueprintable)
class THEIMMORTALGAME_API UTIGPieceManager : public UObject
{
	GENERATED_BODY()
public:
	using Army	   = TArray<ATIGPiece*>;
	using PlayerID = int32;

	using PlayerIDToArmy = TMap<PlayerID, Army>;

public:
	UTIGPieceManager();
	~UTIGPieceManager();

	ATIGPiece* CreatePiece(ATIGPlayerState& Player, EPieceType Type, FTransform& Transform); 

private:
	PlayerIDToArmy ActivePieces; 
	PlayerIDToArmy LostPieces;

	UPROPERTY(EditDefaultsOnly, Category = "Piece Types")
	TSubclassOf<ATIGPiece> PieceClass[static_cast<uint8>(EPieceType::NUM)];
};
