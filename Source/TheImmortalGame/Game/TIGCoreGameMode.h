// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "Game Systems/TIGArena.h"


#include "TIGCoreGameMode.generated.h"

/**
 * 
 */
class APlayerController;
class ATIGGridBoard;
class UTIGPieceManager;



UCLASS()
class THEIMMORTALGAME_API ATIGCoreGameMode : public AGameMode
{
	GENERATED_BODY()

public:
		ATIGCoreGameMode();

		virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
		virtual void StartPlay() override;
private:
	UTIGArena*	Arena;

	UPROPERTY(EditDefaultsOnly, Category = "Pieces")
	TSubclassOf<UTIGPieceManager> PieceManagerClass;

private:
	// Initialisation
	void InitArena();
	UTIGPieceManager* CreatePieceManager();
	ATIGGridBoard* FetchGameBoard();
};
