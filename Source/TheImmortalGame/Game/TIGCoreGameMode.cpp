// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGCoreGameMode.h"

#include "CoreGameUtilities.h"

#include "Player/TIGCameraPawnController.h"
#include "Player/TIGPlayerState.h"

#include "Board/TIGGridBoard.h"

#include "Pieces/TIGPieceManager.h"

#include "Kismet/GameplayStatics.h"

#include "Engine/World.h"

#include "EngineGlobals.h"

ATIGCoreGameMode::ATIGCoreGameMode() 
{
}

void  ATIGCoreGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	InitOptions();
	InitArena();
}

void ATIGCoreGameMode::InitArena()
{
	Arena = NewObject<UTIGArena>(this, ArenaClass);
	Arena->InitArena(LogicalArena);
	check(Arena != nullptr && "ATIGCoreGameMode : Failed to create Arena");

	check(StartingPieceLayout != nullptr && "A Starting Piece Table is required"); 
	LogicalArena.Init({ CoreGameUtilities::DEFAULT_BOARD_NUM_ROWS, CoreGameUtilities::DEFAULT_BOARD_NUM_COLS }, *StartingPieceLayout);
}

void ATIGCoreGameMode::InitOptions()
{
	check(GameOptionsClass != nullptr && "ATIGCoreGameMode : No GameOptionClass Set");
	GameOptions = NewObject<UTIGGameModeOptions>(this, *GameOptionsClass);
}

