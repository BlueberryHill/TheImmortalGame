// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGCoreGameMode.h"

#include "Player/TIGCameraPawnController.h"
#include "Player/TIGPlayerState.h"

#include "Board/TIGGridBoard.h"

#include "Pieces/TIGPieceManager.h"

#include "Kismet/GameplayStatics.h"

#include "Engine/World.h"

#include "EngineGlobals.h"

ATIGCoreGameMode::ATIGCoreGameMode() 
	: Arena(NewObject<UTIGArena>(UTIGArena::StaticClass()))
	, PieceManagerClass(UTIGPieceManager::StaticClass())
{
	check(PieceManagerClass != nullptr && "ATIGCoreGameMode : No PieceManagerClass Set");
	check(Arena != nullptr && "ATIGCoreGameMode : Failed to create Arena");
}

void ATIGCoreGameMode::StartPlay()
{
	Super::StartPlay();
	Arena->PrepareToStart();
}


void  ATIGCoreGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	InitArena();
}

void ATIGCoreGameMode::InitArena()
{
	UTIGPieceManager* PieceManager = CreatePieceManager();
	ATIGGridBoard* GameBoard = FetchGameBoard();

	Arena->InitArena(*PieceManager, *GameBoard);
}

UTIGPieceManager* ATIGCoreGameMode::CreatePieceManager()
{
	UTIGPieceManager* PieceManager = NewObject<UTIGPieceManager>(this, *PieceManagerClass);
	check(PieceManager != nullptr && "TIGCoreGameMode: Failed to create a PieceManager");

	return PieceManager;
}

ATIGGridBoard* ATIGCoreGameMode::FetchGameBoard()
{
	TArray<AActor*> FoundBoard;
	UGameplayStatics::GetAllActorsOfClass(this, ATIGGridBoard::StaticClass(), FoundBoard);
	check(FoundBoard.Num() == 1 && "TIGCoreGameMode: Only exactly one board per level is currently supported");

	ATIGGridBoard* GameBoard = Cast<ATIGGridBoard>(FoundBoard[0]);
	check(GameBoard != nullptr && "TIGCoreGameMode: Failed to fetch game board from level");

	return GameBoard;
}
