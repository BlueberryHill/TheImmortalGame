// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TIGArenaDelegates.h"

#include "Pieces/TIGLogicalPieceManager.h"

#include "General/LogicalTypes.h"

#include "Game Systems/Movement/TIGMovementManager.h"


/**
 * 
 */

namespace BoardUtility
{
	struct BoardDimensions;
	struct TileCoordinate;
}


class TIGLogicalBoard;
class TIGLogicalTile;
class UDataTable;

enum class EPieceType : uint8;

namespace MovementUtility
{
	enum class EDirection : uint8;
}

namespace TileUtility
{
	enum class ETileState : uint8;
}

//TODO: Template this 
class THEIMMORTALGAME_API TIGLogicalArena
{
	class TilePieceBiMap
	{
		using TilePieceMap = TMap<TIG::TileID, TIG::PieceID>;
		using PieceTileMap = TMap<TIG::PieceID, TIG::TileID>;

	public:
		void PieceSpawned(TIG::PieceID PieceID, TIG::TileID TileID);
		TIG::PieceID  GetPieceOnTile(TIG::TileID TileID) const;
		TIG::TileID	  GetTileForPiece(TIG::PieceID PieceID) const;


	private:
		TilePieceMap TileToPiece;
		PieceTileMap PieceToTile;
	};
public:
	TIGLogicalArena();
	~TIGLogicalArena();

	const TIGLogicalPiece& GetPieceForID(TIG::PieceID PieceID) const;
	const TIGLogicalTile&  GetTileForID(TIG::TileID TileID) const;
	TIG::TileID			   GetTileForPiece(TIG::PieceID PieceID) const;
	TIG::PieceID		   GetPieceForTile(TIG::TileID TileID) const;
	void Init(const BoardUtility::BoardDimensions& Dimensions, const UDataTable& StartingPieceLayout);

	TArray<TIG::TileID>	   GetFreeTilesToMoveTo(TIG::PieceID) const;
	void				   GetNextNFreeTiles(TIG::TileID From, MovementUtility::EDirection Direction, int32 N, TArray<TIG::TileID>& OutTileArray) const;
	TIG::TileID			   GetTileInDirection(TIG::TileID From, MovementUtility::EDirection Direction, int32 NumberOfTilesAway) const;


	bool				   TileIsOccupied(const TIG::TileID ID) const;

	TileUtility::ETileState GetTileState(TIG::TileID ID) const;

	FTIGArenaDelegates Delegates;

private:
	TUniquePtr<TIGLogicalBoard> GameBoard;
	TIGLogicalPieceManager		PieceManager;
	TIGMovementManager			MovementManager; 

	TilePieceBiMap				TilePieceAssociation;

	int32 GetTileAtCoordinate(BoardUtility::TileCoordinate BoardCoordinate) const;

	void InitGameBoard(BoardUtility::BoardDimensions Dimensions);
	void InitPieceManager(const UDataTable& StartingPieceLayout);

	void AddRowOfPieces(const int32 Row, const EPieceType PieceType, TIG::PlayerID OwningPlayerID);
	void AddPiece(const int32 Row, const int32 Col, const EPieceType PieceType, TIG::PlayerID OwningPlayerID);

	void RemoveBlockedTiles(TArray<TIG::TileID>& OutTileArray) const;

};
