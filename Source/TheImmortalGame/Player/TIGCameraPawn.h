// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "General/LogicalTypes.h"

#include "TIGCameraPawn.generated.h"

class USceneComponent;
class USphereComponent;
class USpringArmComponent;
class UCameraComponent;

class ATIGPiece;
class ATIGTile;

UCLASS()
class THEIMMORTALGAME_API ATIGCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATIGCameraPawn();

	void MoveForward(float Value);
	void MoveRight(float Value);

	void AddYaw(float Value);

	void Zoom(float Value);

	void OnPieceSelected(ATIGPiece& Piece);
	void OnTileSelected(ATIGTile& Tile);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraSpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	// Components
	void SetupComponents();
	void CreateCollisionComponent();
	void CreateSpringArmComponent();
	void CreateCameraComponent();


	ATIGPiece* CurrentlySelectedPiece = nullptr;
};
