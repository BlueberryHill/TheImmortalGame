// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGPieceManager.h"

#include "Pieces/TIGPiece.h"

#include "Player/TIGPlayerState.h"

#include "Materials/MaterialInstanceDynamic.h"

#include "Math.h"

#include "Engine/World.h"

UTIGPieceManager::UTIGPieceManager()
{
}

UTIGPieceManager::~UTIGPieceManager()
{
}

ATIGPiece* UTIGPieceManager::CreatePiece(const ATIGPlayerState& Player, EPieceType Type, PieceID ID, const FTransform& Transform)
{
	TSubclassOf<ATIGPiece> PieceClassToSpawn = PieceClass[static_cast<uint8>(Type)];
	check(PieceClassToSpawn != nullptr && "TIGPieceManager - Critical Error: Missing Piece Class");

	ATIGPiece* NewPiece = GetWorld()->SpawnActor<ATIGPiece>(*PieceClassToSpawn, Transform);

	//#TODO: Refactor
	UMaterialInstanceDynamic* DynamicBaseMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
	NewPiece->SetBaseMaterial(DynamicBaseMaterial);
	NewPiece->SetBaseColour({1.0f, 0.0f, 0.0f}); //#TODO Get colour from player
	
	if (NewPiece)
	{
		ActivePieces.Emplace(NewPiece, ID);
		//#TODO: Refactor
		Army* PlayerArmy = PlayerPieces.Find(Player.GetUniqueID());
		if (PlayerArmy)
		{
			PlayerArmy->Add(NewPiece);
		}
		else
		{
			PlayerPieces.Emplace(Player.GetUniqueID(), TArray<ATIGPiece*>{ NewPiece });
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TIGPieceManager : Tried to spawn a new piece and failed"));
	}

	return NewPiece;
}

TIG::PieceID UTIGPieceManager::GetPieceID(const ATIGPiece & Piece) const
{
	check(ActivePieces.Contains(&Piece) && "GetPieceID() - Piece Missing From ID Map");
	return *ActivePieces.Find(&Piece);
}

void UTIGPieceManager::OnPieceSelected(ATIGPiece& Piece)
{
	Piece.SetBaseColour({ 0.0f, 0.0f, 1.0f }); //#TODO Don't hardcode this
}

void UTIGPieceManager::OnPieceDeselected(ATIGPiece & Piece)
{
	Piece.SetBaseColour({ 1.0f, 0.0f, 0.0f });
}
