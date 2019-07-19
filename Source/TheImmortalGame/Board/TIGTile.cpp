// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGTile.h"

#include "General/Collision.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values
ATIGTile::ATIGTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupComponents();
}

void ATIGTile::SetMaterial(UMaterial* NewMaterial)
{
	TileMesh->SetMaterial(TileUtility::TILE_MESH_MATERIAL_INDEX, NewMaterial);
	//TileMesh->GetStaticMesh()->SetMaterial(TileUtility::TILE_MESH_MATERIAL_INDEX, NewMaterial);
}

// Called when the game starts or when spawned
void ATIGTile::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ATIGTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATIGTile::SetupComponents()
{
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	TileMesh->SetCollisionResponseToChannel(TILE_TRACE_CHANNEL, ECollisionResponse::ECR_Block);
	RootComponent = TileMesh;
}

