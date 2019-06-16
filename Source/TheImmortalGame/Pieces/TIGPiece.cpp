// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGPiece.h"

// Sets default values
ATIGPiece::ATIGPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupComponents();
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
	RootComponent = PieceMesh;
}

