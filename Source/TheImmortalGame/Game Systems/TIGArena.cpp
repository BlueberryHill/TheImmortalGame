// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGArena.h"

#include "Pieces/TIGPieceManager.h"
#include "Pieces/TIGPiece.h"
#include "Board/TIGGridBoard.h"

#include "Board/BoardUtility.h"

#include "Database/TIGStartingPieces.h"

#include "Engine/DataTable.h"
#include "Engine/World.h"

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

	ATIGPlayerState* FakeState = NewObject<ATIGPlayerState>(ATIGPlayerState::StaticClass());
	if (StartingPieces)
	{
		for (auto& KeyRowPair : StartingPieces->GetRowMap())
		{
			FTIGStartingPieces* PieceRow = (FTIGStartingPieces*)(KeyRowPair.Value); //#TODO: Safer to get all names then extract rows from names
			if (PieceRow->Col >= 0)
			{
				AddPiece(PieceRow->Row, PieceRow->Col, PieceRow->PieceType, *FakeState);
			}
			else
			{
				AddRowOfPieces(PieceRow->Row, PieceRow->PieceType, *FakeState);
			}
		}
	}

}

void UTIGArena::AddRowOfPieces(const int32 Row, const EPieceType PieceType, ATIGPlayerState& OwningPlayer)
{
	check(GameBoard != nullptr && "TIGArena - No GameBoard");

	for (int32 Col = 0; Col < GameBoard->GetNumColumns(); ++Col)
	{
		AddPiece(Row, Col, PieceType, OwningPlayer);
	}
}

void UTIGArena::AddPiece(const int32 Row, const int32 Col, const EPieceType PieceType, ATIGPlayerState& OwningPlayer)
{
	check(GameBoard != nullptr && "TIGArena - No GameBoard");
	check(PieceManager != nullptr && "TIGArena - No PieceManager");

	//GameBoard->GetTilePieceLocation(); //GetTileCentre() + Offset
	FTransform Translation(BoardUtility::OriginToTileCentreOffset({ Row, Col }));
	FTransform SpawnTransform = GameBoard->GetTransform() + Translation;
	ATIGPiece* Piece = PieceManager->CreatePiece(OwningPlayer, PieceType, SpawnTransform); // GetWorld()->SpawnActor<ATIGPiece>(SpawnTransform.GetTranslation(), SpawnTransform.GetRotation().Rotator());
	Piece->AttachToActor(GameBoard, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	//Piece->SetMaterial(CoordinatesToMaterial(Row, Col)); // PlayerState PlayerColour
	//Tile->SetState(Occupied);
}



