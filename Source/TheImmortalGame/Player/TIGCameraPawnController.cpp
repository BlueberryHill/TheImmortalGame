// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGCameraPawnController.h"

#include "TIGCameraPawn.h"

#include "General/Collision.h"

#include "Pieces/TIGPiece.h"
#include "Board/TIGTile.h"

#include "EngineGlobals.h"



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
	InputComponent->BindAxis("ZoomIn", this, &ATIGCameraPawnController::ZoomIn);
}

void ATIGCameraPawnController::SetupActionBindings()
{
	InputComponent->BindAction("Select", IE_Pressed, this, &ATIGCameraPawnController::SelectAttempt);
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

void ATIGCameraPawnController::ZoomIn(float Value)
{
	if (bMovementEnabled == true && PossessedPawn)
	{
		PossessedPawn->Zoom(Value * CalculateZoomSpeed());
	}
}

void ATIGCameraPawnController::SelectAttempt()
{
	if (TrySelectPawnUnderCursor() == true)
	{
		return;
	}
	
	if (TrySelectTileUnderCursor() == true)
	{
		return;
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

float ATIGCameraPawnController::CalculateZoomSpeed()
{
	//#TODO: Make tick independent. Implement this after (Make a function of spring arm length?). Clamp between min and max speed
	return 100.0f;
}

bool ATIGCameraPawnController::TrySelectPawnUnderCursor()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(PIECE_TRACE_CHANNEL, false, HitResult);
	ATIGPiece* SelectedPiece = Cast<ATIGPiece>(HitResult.GetActor());
	if (SelectedPiece)
	{
		PossessedPawn->OnPieceSelected(*SelectedPiece);
	}
	return SelectedPiece != nullptr;
}

bool ATIGCameraPawnController::TrySelectTileUnderCursor()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(TILE_TRACE_CHANNEL, false, HitResult);
	ATIGTile* SelectedTile = Cast<ATIGTile>(HitResult.GetActor());
	if (SelectedTile)
	{
		PossessedPawn->OnTileSelected(*SelectedTile);
	}

	return SelectedTile != nullptr;
}
