// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGCameraPawnController.h"

#include "TIGCameraPawn.h"

ATIGCameraPawnController::ATIGCameraPawnController()
{
	bShowMouseCursor = true;
}


void ATIGCameraPawnController::BeginPlay()
{
	PossessedPawn = Cast<ATIGCameraPawn>(GetPawn());
	check(PossessedPawn != nullptr && "ACameraPawnPlayerController - Failed to cast PossessedPawn");
}

void ATIGCameraPawnController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	SetupAxisBindings();
	SetupActionBindings();
}

void ATIGCameraPawnController::SetupAxisBindings()
{
	InputComponent->BindAxis("MoveForward", this, &ATIGCameraPawnController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATIGCameraPawnController::MoveRight);
	InputComponent->BindAxis("RotateClockwise", this, &ATIGCameraPawnController::RotateClockwise);
}

void ATIGCameraPawnController::SetupActionBindings()
{

}

void ATIGCameraPawnController::MoveForward(float Value)
{
	if (bMovementEnabled == true && PossessedPawn)
	{
		PossessedPawn->MoveForward(Value * CalculateMovementSpeed());
	}
}

void ATIGCameraPawnController::MoveRight(float Value)
{
	if (bMovementEnabled == true && PossessedPawn)
	{
		PossessedPawn->MoveRight(Value * CalculateMovementSpeed());
	}
}

void ATIGCameraPawnController::RotateClockwise(float Value)
{
	if (bMovementEnabled == true && PossessedPawn)
	{
		PossessedPawn->AddYaw(Value * CalculateRotationSpeed());
	}
}

float ATIGCameraPawnController::CalculateMovementSpeed()
{
	//#TODO: Make tick independent. Implement this after zoom (Make a function of spring arm length). Clamp between min and max speed
	return 10.0f;
}

float ATIGCameraPawnController::CalculateRotationSpeed()
{
	//#TODO: Make tick independent. Implement this after (Make a function of spring arm length?). Clamp between min and max speed
	return 5.0f;
}
