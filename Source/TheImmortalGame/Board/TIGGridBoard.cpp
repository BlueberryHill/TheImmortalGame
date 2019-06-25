// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGGridBoard.h"

#include "TIGTile.h"

#include "BoardConstants.h"

#include "Engine/World.h"

// Sets default values
ATIGGridBoard::ATIGGridBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATIGGridBoard::BeginPlay()
{
	Super::BeginPlay();
}

// Note: This is called every time you a property of the board is changed
void ATIGGridBoard::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	check(NumColumns > 0 && "NumColumns must be positive");
	check(NumRows > 0 && "NumRows must be positive");
	
	if (HasAnyFlags(EObjectFlags::RF_Transient)) // Transient check fixes a weird issue with some tiles not getting destroyed in editor.
	{
		return;
	}

	DestroyAllTiles();
	CreateBoard(Transform);
}

void ATIGGridBoard::CreateBoard(const FTransform & Transform)
{
	for (int32 Row = 0; Row < NumRows; ++Row)
	{
		for (int32 Col = 0; Col < NumColumns; ++Col)
		{
			AddTile({ Row, Col }, Transform);
		}
	}
}

// Called every frame
void ATIGGridBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATIGGridBoard::BeginDestroy()
{
	Super::BeginDestroy();

	DestroyAllTiles();
}

void ATIGGridBoard::AddTile(BoardUtility::TileCoordinate Coordinate, const FTransform & Transform)
{
	if (GetWorld() == nullptr || TileClass == nullptr)
	{
		return;
	}

	ValidateCoordinate(Coordinate);

	ATIGTile* Tile = SpawnTile(Coordinate, Transform);
	AddTileToBoard(Tile);
	
	TileUtility::ETileColour Colour = BoardUtility::CoordinateToTileColour(Coordinate);
	Tile->SetColour(Colour);
	Tile->SetState(TileUtility::ETileState::IDLE);
	if (Colour == TileUtility::ETileColour::DARK)
	{
		Tile->SetMaterial(DarkMaterialsPerState[static_cast<uint8>(TileUtility::ETileState::IDLE)]);
	}
	else
	{
		Tile->SetMaterial(LightMaterialsPerState[static_cast<uint8>(TileUtility::ETileState::IDLE)]);
	}
}

ATIGTile* ATIGGridBoard::SpawnTile(const BoardUtility::TileCoordinate& Coordinate, const FTransform& Transform)
{
	FTransform OffsetFromOrigin = FTransform(BoardUtility::OriginToTileCentreOffset(Coordinate));
	FTransform SpawnTransform = Transform + OffsetFromOrigin;
	return GetWorld()->SpawnActor<ATIGTile>(TileClass, SpawnTransform.GetTranslation(), SpawnTransform.GetRotation().Rotator());
}

void ATIGGridBoard::AddTileToBoard(ATIGTile* Tile)
{
	Tile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	Tiles.Add(Tile);
}


void ATIGGridBoard::DestroyAllTiles()
{
	for (ATIGTile* Tile : Tiles)
	{
		if (Tile)
		{
			Tile->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
			Tile->Destroy();
		}
	}
	Tiles.Empty();
}

void ATIGGridBoard::ValidateCoordinate(BoardUtility::TileCoordinate Coordinate)
{
	check(Coordinate.Row >= 0		  && "AddTile: Invalid Row Coordinate");
	check(Coordinate.Col >= 0		  && "AddTile: Invalid Column Coordinate");
	check(Coordinate.Row < NumRows    && "AddTile: Invalid Row Coordinate");
	check(Coordinate.Col < NumColumns && "AddTile: Invalid Column Coordinate");
}

