// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "Game Systems/TIGArena.h"
#include "Game Systems/TIGLogicalArena.h"

#include "Game/TIGGameModeOptions.h"

#include "Templates/UniquePtr.h"

#include "TIGCoreGameMode.generated.h"

/**
 * 
 */
class APlayerController;
class ATIGGridBoard;
class UTIGPieceManager;
class UTIGGameModeOptions;


UCLASS()
class THEIMMORTALGAME_API ATIGCoreGameMode : public AGameMode
{
	GENERATED_BODY()

public:
		ATIGCoreGameMode();

		virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

		const UTIGGameModeOptions& GetOptions() { return *GameOptions; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Arena")
	TSubclassOf<UTIGArena>	ArenaClass;

	UPROPERTY(EditDefaultsOnly, Category = "Options")
	TSubclassOf<UTIGGameModeOptions> GameOptionsClass;

	UPROPERTY(EditDefaultsOnly, Category = "Pieces")
	UDataTable* StartingPieceLayout;

private:
	UTIGArena* Arena = nullptr;
	TIGLogicalArena LogicalArena;

	UTIGGameModeOptions* GameOptions = nullptr;
	

	// Initialisation
	void InitArena();
	void InitOptions();
};
