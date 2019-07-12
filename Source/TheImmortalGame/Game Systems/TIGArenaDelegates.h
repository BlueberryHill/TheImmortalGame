// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FBoardCreated, int32 /* Num Rows */, int32 /* Num Rows */);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FPieceSpawned, int32 /* Row */, int32 /* Col */, int32 /*PieceID*/);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FTileSpawned, int32 /* Row */, int32 /* Col */, int32 /*TileID*/);


struct FTIGArenaDelegates
{
	FBoardCreated BoardCreated;
	FPieceSpawned PieceSpawned;
	FTileSpawned  TileSpawned;
};
