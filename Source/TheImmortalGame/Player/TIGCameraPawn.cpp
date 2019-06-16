// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGCameraPawn.h"

#include "CameraUtility.h"

#include "Camera/CameraComponent.h"

#include "Components/SphereComponent.h"

#include "GameFramework/SpringArmComponent.h"

#include "EngineGlobals.h"


// Sets default values
ATIGCameraPawn::ATIGCameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupComponents();
}

// Called when the game starts or when spawned
void ATIGCameraPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATIGCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATIGCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ATIGCameraPawn::SetupComponents()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CreateCollisionComponent();
	CreateSpringArmComponent();
	CreateCameraComponent();
}

void ATIGCameraPawn::CreateCollisionComponent()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->InitSphereRadius(CameraUtility::DEFAULT_COLLISION_RADIUS);
	CollisionComponent->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->BodyInstance.SetResponseToAllChannels(ECR_Block);
	CollisionComponent->BodyInstance.SetResponseToChannel(ECC_Camera, ECR_Ignore);
}

void ATIGCameraPawn::CreateSpringArmComponent()
{
	CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	CameraSpringArmComponent->SetupAttachment(RootComponent);
	//OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	CameraSpringArmComponent->TargetArmLength = CameraUtility::DEFAULT_SPRING_ARM_LENGTH;
	CameraSpringArmComponent->SetRelativeRotation(FQuat(CameraUtility::Y_AXIS, CameraUtility::DEFAULT_SPRING_ARM_ROTATION));
	CameraSpringArmComponent->bEnableCameraLag = true;
	CameraSpringArmComponent->CameraLagSpeed = CameraUtility::DEFAULT_SPRING_ARM_LAG_SPEED;
}

void ATIGCameraPawn::CreateCameraComponent()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraSpringArmComponent, USpringArmComponent::SocketName);
}


void ATIGCameraPawn::MoveForward(float Value)
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * Value);
}

void ATIGCameraPawn::MoveRight(float Value)
{
	SetActorLocation(GetActorLocation() + GetActorRightVector() * Value);
}

void ATIGCameraPawn::AddYaw(float Value)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Add(0.0f, Value, 0.0f);
	SetActorRotation(NewRotation);
}