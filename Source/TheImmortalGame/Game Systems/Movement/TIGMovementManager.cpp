// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGMovementManager.h"

#include "../TIGLogicalArena.h"

#include "Pieces/TIGLogicalPiece.h"


TIGMovementManager::TIGMovementManager()
{
}

TIGMovementManager::~TIGMovementManager()
{
}

TArray<TIG::TileID> TIGMovementManager::CalculatePossibleMovesForPiece(TIG::PieceID PieceID, const TIGLogicalArena & Arena)
{
	TArray<TIG::TileID> ReachableTiles;
	const TIGLogicalPiece& Piece = Arena.GetPieceForID(PieceID);


	return ReachableTiles;
}
