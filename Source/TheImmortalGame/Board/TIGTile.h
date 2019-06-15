// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TileUtility.h"

#include "TIGTile.generated.h"

class UMaterial;

UCLASS()
class THEIMMORTALGAME_API ATIGTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATIGTile();

	void SetColour(TileUtility::ETileColour NewColour) { Colour = NewColour; };
	void SetState(TileUtility::ETileState NewState) { State = NewState; }
	void SetMaterial(UMaterial* NewMaterial);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Static Mesh")
	UStaticMeshComponent* TileMesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SetupComponents();

	TileUtility::ETileColour Colour = TileUtility::ETileColour::NO_COLOUR;
	TileUtility::ETileState  State  = TileUtility::ETileState::IDLE;
};
