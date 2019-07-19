// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGPiece.h"

#include "General/Collision.h"

#include "Materials/MaterialInstanceDynamic.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values
ATIGPiece::ATIGPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupComponents();
}

void ATIGPiece::SetBaseColour(const FVector& BaseColour)
{
	DynamicBaseMaterial->SetVectorParameterValue("BaseColour", BaseColour);
}

void ATIGPiece::SetBaseMaterial(UMaterialInstanceDynamic* BaseMat)
{
	DynamicBaseMaterial = BaseMat;
	PieceMesh->SetMaterial(0, DynamicBaseMaterial); //#TODO: Identify material indices
}

// Called when the game starts or when spawned
void ATIGPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATIGPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATIGPiece::SetupComponents()
{
	PieceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	PieceMesh->SetCollisionResponseToChannel(PIECE_TRACE_CHANNEL, ECollisionResponse::ECR_Block);
	RootComponent = PieceMesh;
}

