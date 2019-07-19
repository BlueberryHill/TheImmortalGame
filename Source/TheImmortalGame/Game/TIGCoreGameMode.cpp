// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGCoreGameMode.h"

#include "CoreGameUtilities.h"
#include "TIGCoreGameState.h"

#include "Game Systems/TIGLogicalArena.h"

#include "Player/TIGCameraPawnController.h"
#include "Player/TIGPlayerState.h"

#include "Board/TIGGridBoard.h"

#include "Pieces/TIGPieceManager.h"

#include "Kismet/GameplayStatics.h"

#include "Engine/World.h"

#include "EngineGlobals.h"

ATIGCoreGameMode::ATIGCoreGameMode() 
{
	GameStateClass = ATIGCoreGameState::StaticClass();
}

void  ATIGCoreGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	InitOptions();
}

void ATIGCoreGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	InitArena();
}

void ATIGCoreGameMode::InitArena()
{
	UTIGArena* ArenaView = NewObject<UTIGArena>(this, ArenaClass);
	check(ArenaView != nullptr && "ATIGCoreGameMode : Failed to create Arena");

	TIGLogicalArena* LogicalArena = new TIGLogicalArena;
	ArenaView->InitArena(*LogicalArena, LogicalArena->Delegates);

	check(StartingPieceLayout != nullptr && "A Starting Piece Table is required"); 
	LogicalArena->Init({ CoreGameUtilities::DEFAULT_BOARD_NUM_ROWS, CoreGameUtilities::DEFAULT_BOARD_NUM_COLS }, *StartingPieceLayout);

	ATIGCoreGameState* TIGGameState = Cast<ATIGCoreGameState>(GameState);
	TIGGameState->Init(*ArenaView, *LogicalArena);
}

void ATIGCoreGameMode::InitOptions()
{
	check(GameOptionsClass != nullptr && "ATIGCoreGameMode : No GameOptionClass Set");
	GameOptions = NewObject<UTIGGameModeOptions>(this, *GameOptionsClass);
}

