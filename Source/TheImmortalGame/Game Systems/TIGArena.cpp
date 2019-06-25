// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGArena.h"

#include "Pieces/TIGPieceManager.h"
#include "Board/TIGGridBoard.h"


UTIGArena::UTIGArena() 
{
}

UTIGArena::~UTIGArena()
{
}

void UTIGArena::InitArena(UTIGPieceManager& NewPieceManager, ATIGGridBoard& NewGameBoard)
{
	PieceManager = &NewPieceManager;
	GameBoard = &NewGameBoard;
}

#include "Player/TIGPlayerState.h"
void UTIGArena::PrepareToStart()
{
	check(GameBoard != nullptr && "TIGArena - No GameBoard");
	check(PieceManager != nullptr && "TIGArena - No PieceManager");

	FTransform PawnTrans(FVector(0.0f, 0.0f, 100.0f));
	ATIGPlayerState* FakeState = NewObject<ATIGPlayerState>(ATIGPlayerState::StaticClass());
	PieceManager->CreatePiece(*FakeState, EPieceType::PAWN, PawnTrans);
}



