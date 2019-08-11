// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGGridBoard.h"

#include "TIGTile.h"

#include "BoardConstants.h"

#include "Engine/World.h"

#include "General/EnumUtil.h"

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

	//check(NumColumns > 0 && "NumColumns must be positive");
	//check(NumRows > 0 && "NumRows must be positive");
	//
	//if (HasAnyFlags(EObjectFlags::RF_Transient)) // Transient check fixes a weird issue with some tiles not getting destroyed in editor.
	//{
	//	return;
	//}

	//DestroyAllTiles();
	//CreateBoard(Transform);
}

void ATIGGridBoard::CreateBoard(const FTransform & Transform)
{
	//for (int32 Row = 0; Row < NumRows; ++Row)
	//{
	//	for (int32 Col = 0; Col < NumColumns; ++Col)
	//	{
	//		AddTile({ Row, Col }, Transform);
	//	}
	//}
}

// Called every frame
void ATIGGridBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATIGGridBoard::BeginDestroy()
{
	Super::BeginDestroy();

	//DestroyAllTiles();
}

ATIGTile* ATIGGridBoard::AddTile(BoardUtility::TileCoordinate Coordinate, TIG::TileID TileID)
{
	check(GetWorld() != nullptr && "AddTile() - No valid game world");
	check(TileClass != nullptr && "AddTile() - No Tile Class assigned");
	ValidateCoordinate(Coordinate);

	ATIGTile* Tile = SpawnTile(Coordinate, GetTransform());
	AddTileToBoard(Tile);

	TileUtility::ETileColour Colour = BoardUtility::CoordinateToTileColour(Coordinate);
	Tile->SetColour(Colour);
	Tile->SetState(TileUtility::ETileState::IDLE);
	TileIDMap.AddPair(Tile, TileID );
	SetTileMaterialToState(TileID, TileUtility::ETileState::IDLE);

	return Tile;
}

TIG::TileID ATIGGridBoard::GetTileID(const ATIGTile& Tile) const
{
	return TileIDMap.GetID(&Tile);
}

void ATIGGridBoard::SetTileMaterialToState(TIG::TileID TileID, TileUtility::ETileState State)
{
	ATIGTile* Tile = TileIDMap.GetTile(TileID);
	if (Tile->GetColour() == TileUtility::ETileColour::DARK) 
	{
		Tile->SetMaterial(DarkMaterialsPerState[TIG::enum_to_value(State)]); 
	}
	else
	{
		Tile->SetMaterial(LightMaterialsPerState[TIG::enum_to_value(State)]);
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

void ATIGGridBoard::TileIDBiMap::AddPair(ATIGTile* Tile, TIG::TileID ID)
{
	TileToTileID.Emplace(Tile, ID);
	TileIDToTile.Emplace(ID, Tile);
}

ATIGTile * ATIGGridBoard::TileIDBiMap::GetTile(TIG::TileID TileID) const
{
	check(TileIDToTile.Find(TileID) && "Requesting Tile ID which isn't present in BiMap");
	return *TileIDToTile.Find(TileID);
}

TIG::TileID ATIGGridBoard::TileIDBiMap::GetID(const ATIGTile* Tile) const
{
	check(TileToTileID.Find(Tile) && "Requesting Tile ID which isn't present in BiMap");
	return *TileToTileID.Find(Tile);
}
