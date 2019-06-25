// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGPieceManager.h"

#include "Pieces/TIGPiece.h"

#include "Player/TIGPlayerState.h"


#include "Engine/World.h"

UTIGPieceManager::UTIGPieceManager()
{
}

UTIGPieceManager::~UTIGPieceManager()
{
}

ATIGPiece* UTIGPieceManager::CreatePiece(ATIGPlayerState& Player, EPieceType Type, FTransform& Transform)
{
	TSubclassOf<ATIGPiece> PieceClassToSpawn = PieceClass[static_cast<uint8>(Type)];
	check(PieceClassToSpawn != nullptr && "TIGPieceManager - Critical Error: Missing Piece Class");

	ATIGPiece* NewPiece = GetWorld()->SpawnActor<ATIGPiece>(*PieceClassToSpawn, Transform);
	if (NewPiece)
	{
		Army* PlayerArmy = ActivePieces.Find(Player.GetUniqueID());
		if (PlayerArmy)
		{
			PlayerArmy->Add(NewPiece);
		}
		else
		{
			ActivePieces.Emplace(Player.GetUniqueID(), TArray<ATIGPiece*>{ NewPiece });
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TIGPieceManager : Tried to spawn a new piece and failed"));
	}

	return NewPiece;
}
