// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGArena.h"

#include "TIGLogicalArena.h" 
#include "TIGArenaDelegates.h"

#include "Pieces/TIGLogicalPiece.h"
#include "Pieces/TIGPieceManager.h"
#include "Pieces/TIGPiece.h"

#include "Player/TIGPlayerState.h"

#include "Board/TIGGridBoard.h"
#include "Board/BoardUtility.h"

#include "Game/TIGCoreGameMode.h"
#include "Game/TIGGameModeOptions.h"

#include "Engine/World.h"
#include "EngineGlobals.h"
#include "Engine.h"

UTIGArena::UTIGArena() 
{
}

UTIGArena::~UTIGArena()
{
}

void UTIGArena::InitArena(TIGLogicalArena& Arena) 
{

	LogicalArena = &Arena;

	ATIGCoreGameMode* GameMode = Cast<ATIGCoreGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		PieceManager = NewObject<UTIGPieceManager>(this, *GameMode->GetOptions().GetPieceManagerClass());
		check(PieceManager != nullptr && "TIGArena - No PieceManager");

		SetupDelegates(Arena);
	}
}

void UTIGArena::SetupDelegates(TIGLogicalArena& Arena)
{
	FTIGArenaDelegates& Delegates = Arena.Delegates;
	Delegates.BoardCreated.AddUObject(this, &UTIGArena::BoardCreated);
	Delegates.PieceSpawned.AddUObject(this, &UTIGArena::PieceCreated);
	Delegates.TileSpawned.AddUObject(this, &UTIGArena::TileCreated);
}


void UTIGArena::BoardCreated(int32 NumRows, int32 NumCols)
{
	ATIGCoreGameMode* GameMode = Cast<ATIGCoreGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		FVector Location(0.0f);
		FRotator Rotation(0.0f);
		FActorSpawnParameters SpawnInfo;

		GameBoard = GetWorld()->SpawnActor<ATIGGridBoard>(*GameMode->GetOptions().GetBoardClass(), Location, Rotation, SpawnInfo);
		check(GameBoard != nullptr && "TIGArena - No GameBoard");
	}
}

void UTIGArena::AddRowOfPieces(int32 Row, EPieceType PieceType, const ATIGPlayerState& OwningPlayer)
{
	check(GameBoard != nullptr && "TIGArena - No GameBoard");

	for (int32 Col = 0; Col < GameBoard->GetNumColumns(); ++Col)
	{
		AddPiece(Row, Col, PieceType, OwningPlayer);
	}
}

void UTIGArena::PieceCreated(int32 Row, int32 Col, int32 PieceID)
{
	const TIGLogicalPiece& CreatedPiece = LogicalArena->GetPieceForID(PieceID);
	EPieceType Type = CreatedPiece.GetType();

	//#TODO: Remove after creating multiple players
	ATIGPlayerState* FakeState = NewObject<ATIGPlayerState>(ATIGPlayerState::StaticClass());
	AddPiece(Row, Col, Type, *FakeState);
}

void UTIGArena::TileCreated(int32 Row, int32 Col, int32 TileID)
{
	GameBoard->AddTile({Row, Col});
}

void UTIGArena::AddPiece(int32 Row, int32 Col, EPieceType PieceType, const ATIGPlayerState& OwningPlayer)
{
	check(GameBoard != nullptr && "TIGArena - No GameBoard");
	check(PieceManager != nullptr && "TIGArena - No PieceManager");

	FTransform Translation(BoardUtility::OriginToTileCentreOffset({ Row, Col }));
	FTransform SpawnTransform = GameBoard->GetTransform() + Translation;
	ATIGPiece* Piece = PieceManager->CreatePiece(OwningPlayer, PieceType, SpawnTransform);
	Piece->AttachToActor(GameBoard, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
}



