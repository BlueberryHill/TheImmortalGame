// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TIGCameraPawnController.generated.h"

/**
 *
 */

class ATIGCameraPawn;

UCLASS()
class THEIMMORTALGAME_API ATIGCameraPawnController : public APlayerController
{
	GENERATED_BODY()

public:
	ATIGCameraPawnController();

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

protected:
	ATIGCameraPawn* PossessedPawn = nullptr;

	UPROPERTY(BlueprintReadWrite)
	bool bMovementEnabled = true;
	//float MinSpeed;
	//float MaxSpeed;

	//// Axis Bindings
	void SetupAxisBindings();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void RotateClockwise(float Value);

	//// Action Bindings
	void SetupActionBindings();

private:
	// Movement
	float CalculateMovementSpeed();
	float CalculateRotationSpeed();


};
