// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TIGArenaDelegates.h"

#include "Pieces/TIGLogicalPieceManager.h"


/**
 * 
 */

namespace BoardUtility
{
	struct BoardDimensions;
	struct TileCoordinate;
}


class TIGLogicalBoard;
class UDataTable;

enum class EPieceType : uint8;


class THEIMMORTALGAME_API TIGLogicalArena
{
	class TilePieceBiMap
	{
		using TilePieceMap = TMap<int32, int32>;
		using PieceTileMap = TMap<int32, int32>;

	public:
		void PieceSpawned(TIG::PieceID PieceID, TIG::TileID TileID);
		TIG::TileID  GetPieceOnTile(TIG::TileID TileID) const;
		TIG::PieceID GeTileForPiece(TIG::PieceID PieceID) const;
	private:
		TilePieceMap TileToPiece;
		PieceTileMap PieceToTile;
	};
public:
	TIGLogicalArena();
	~TIGLogicalArena();

	const TIGLogicalPiece& GetPieceForID(int32 PieceID) const;
	void Init(const BoardUtility::BoardDimensions& Dimensions, const UDataTable& StartingPieceLayout);

	FTIGArenaDelegates Delegates;

private:
	TUniquePtr<TIGLogicalBoard> GameBoard;
	TIGLogicalPieceManager PieceManager;

	TilePieceBiMap TilePieceAssociation;

	int32 GetTileAtCoordinate(BoardUtility::TileCoordinate BoardCoordinate) const;

	void InitGameBoard(BoardUtility::BoardDimensions Dimensions);
	void InitPieceManager(const UDataTable& StartingPieceLayout);

	void AddRowOfPieces(const int32 Row, const EPieceType PieceType, TIG::PlayerID OwningPlayerID);
	void AddPiece(const int32 Row, const int32 Col, const EPieceType PieceType, TIG::PlayerID OwningPlayerID);

};
