// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TIGCameraPawn.generated.h"

class USceneComponent;
class USphereComponent;
class USpringArmComponent;
class UCameraComponent;

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
};