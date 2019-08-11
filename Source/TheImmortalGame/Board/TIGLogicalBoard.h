// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BoardUtility.h"

#include "General/LogicalTypes.h"

namespace MovementUtility
{
	enum class EDirection : uint8;
}

class TIGLogicalTile;
/**
 * 
 */
class THEIMMORTALGAME_API TIGLogicalBoard
{
	using Tile = TIGLogicalTile;
	using UniquePtrTile = TUniquePtr<Tile>;
	using TileRow = TArray<UniquePtrTile>;
	using Board = TArray<TileRow>;

	using IDToTileMap = TMap<TIG::TileID, Tile*>;
public:
	TIGLogicalBoard(BoardUtility::BoardDimensions);
	~TIGLogicalBoard();

	TIGLogicalBoard(const TIGLogicalBoard&) = delete;
	TIGLogicalBoard& operator=(const TIGLogicalBoard&) = delete;

	int32 GetNumCols() const { return Dimensions.NumCols; }
	int32 GetNumRows() const { return Dimensions.NumRows; }

	const TIGLogicalTile&  AddTile(int32 Row, int32 Col);
	TIG::TileID GetTileAtCoordinate(BoardUtility::TileCoordinate Coordinate) const; 
	const TIGLogicalTile& GetTileForID(TIG::TileID TileID) const;

	void GetNextNTiles(const TIGLogicalTile& From, MovementUtility::EDirection Direction, int32 N, TArray<TIG::TileID>& OutTileArray) const;
	void GetNextNTiles(TIG::TileID From, MovementUtility::EDirection Direction, int32 N, TArray<TIG::TileID>& OutTileArray) const;
private:
	Board						  GameBoard;
	BoardUtility::BoardDimensions Dimensions;

	IDToTileMap					  TileIDToTile;

	void InitBoard();

	bool IsValidCoordinate(BoardUtility::TileCoordinate Coordinate) const;
	BoardUtility::TileCoordinate TileToCoordinate(const TIGLogicalTile& Tile) const;
};
