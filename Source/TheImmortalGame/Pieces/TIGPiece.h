// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PieceUtility.h"

#include "TIGPiece.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;

struct FVector;

UCLASS()
class THEIMMORTALGAME_API ATIGPiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATIGPiece();

	void SetBaseColour(const FVector& BaseColour);
	void SetBaseMaterial(UMaterialInstanceDynamic* BaseMat);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Static Mesh")
	UStaticMeshComponent* PieceMesh;

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicBaseMaterial;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SetupComponents();
};
