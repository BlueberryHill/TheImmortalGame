// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TIGLogicalTile.h"

#include "Board/BoardUtility.h"

/**
 * 
 */

class THEIMMORTALGAME_API TIGLogicalBoard
{
public:
	TIGLogicalBoard();
	~TIGLogicalBoard();

private:
	TArray<TIGLogicalTile> Tiles;

	BoardUtility::BoardDimensions Dimensions;
};
