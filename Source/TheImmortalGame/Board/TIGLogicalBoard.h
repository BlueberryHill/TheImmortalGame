// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BoardUtility.h"

#include "General/LogicalTypes.h"

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
public:
	TIGLogicalBoard(BoardUtility::BoardDimensions);
	~TIGLogicalBoard();

	TIGLogicalBoard(const TIGLogicalBoard&) = delete;
	TIGLogicalBoard& operator=(const TIGLogicalBoard&) = delete;

	int32 GetNumCols() { return Dimensions.NumCols; }
	int32 GetNumRows() { return Dimensions.NumRows; }

	const TIGLogicalTile&  AddTile(int32 Row, int32 Col);
	TIG::TileID GetTileAtCoordinate(BoardUtility::TileCoordinate Coordinate); 

private:
	Board GameBoard;
	BoardUtility::BoardDimensions Dimensions;

	void InitBoard();
};
