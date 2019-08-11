// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileUtility.generated.h"

namespace TileUtility
{
	const int32 TILE_MESH_MATERIAL_INDEX = 0;

	UENUM(BlueprintType)
	enum class ETileColour : uint8
	{
		LIGHT,
		DARK,
		NO_COLOUR,

		NUM
	};

	UENUM(BlueprintType)
	enum class ETileState : uint8
	{
		IDLE,			UMETA(DisplayName = "IDLE")
		OCCUPIED,		UMETA(DisplayName = "OCCUPIED")
		HIGHLIGHTED,	UMETA(DisplayName = "HIGHLIGHTED")

		NUM			UMETA(DisplayName = "INVALID")
	};
}
