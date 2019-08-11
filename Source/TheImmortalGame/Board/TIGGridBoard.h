// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BoardUtility.h"
#include "TileUtility.h"

#include "General/LogicalTypes.h"
#include "General/EnumUtil.h"

#include "TIGGridBoard.generated.h"

class ATIGTile;
class UMaterial;

UCLASS()
class THEIMMORTALGAME_API ATIGGridBoard : public AActor
{
	GENERATED_BODY()

	class TileIDBiMap
	{
		using IDTileMap = TMap<TIG::TileID, ATIGTile*>;
		using TileIDMap = TMap<ATIGTile*, TIG::TileID>;

	public:
		void AddPair(ATIGTile*, TIG::TileID);
		ATIGTile*     GetTile(TIG::TileID TileID) const;
		TIG::TileID	  GetID(const ATIGTile*) const;


	private:
		IDTileMap TileIDToTile;
		TileIDMap TileToTileID;
	};
	
public:	
	// Sets default values for this actor's properties
	ATIGGridBoard();

	int32 GetNumColumns() const { return NumColumns; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	void CreateBoard(const FTransform & Transform);

	UPROPERTY(EditDefaultsOnly)
	int32 NumColumns = BoardUtility::DEFAULT_NUM_COLS;

	UPROPERTY(EditDefaultsOnly)
	int32 NumRows = BoardUtility::DEFAULT_NUM_ROWS;

	UPROPERTY(EditDefaultsOnly, Category = "Tiles")
	TSubclassOf<ATIGTile> TileClass;

	//#TODO: It should be possible to have the enum names show up in the editor. Investigate why this isn't working.
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* LightMaterialsPerState[TIG::enum_to_value(TileUtility::ETileState::NUM)];
	
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* DarkMaterialsPerState[TIG::enum_to_value(TileUtility::ETileState::NUM)];

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginDestroy() override;

	ATIGTile* AddTile(BoardUtility::TileCoordinate Coordinate, TIG::TileID TileID);

	TIG::TileID GetTileID(const ATIGTile& Tile) const;

	void SetTileMaterialToState(TIG::TileID TileID, TileUtility::ETileState State);
private:

	void DestroyAllTiles();

	void ValidateCoordinate(BoardUtility::TileCoordinate Coordinate);
	ATIGTile* SpawnTile(const BoardUtility::TileCoordinate& Coordinate, const FTransform& Transform);
	void	  AddTileToBoard(ATIGTile* Tile);


	UPROPERTY()
	TArray<ATIGTile*> Tiles;

	TileIDBiMap TileIDMap;
};
