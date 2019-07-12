// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BoardUtility.h"
#include "TileUtility.h"

#include "TIGGridBoard.generated.h"

class ATIGTile;
class UMaterial;

UCLASS()
class THEIMMORTALGAME_API ATIGGridBoard : public AActor
{
	GENERATED_BODY()
	
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
	UMaterial* LightMaterialsPerState[static_cast<uint8>(TileUtility::ETileState::NUM)];
	
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* DarkMaterialsPerState[static_cast<uint8>(TileUtility::ETileState::NUM)];

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginDestroy() override;

	ATIGTile* AddTile(BoardUtility::TileCoordinate Coordinate);
private:

	void DestroyAllTiles();

	void ValidateCoordinate(BoardUtility::TileCoordinate Coordinate);
	ATIGTile* SpawnTile(const BoardUtility::TileCoordinate& Coordinate, const FTransform& Transform);
	void	  AddTileToBoard(ATIGTile* Tile);


	UPROPERTY()
	TArray<ATIGTile*> Tiles;

};
