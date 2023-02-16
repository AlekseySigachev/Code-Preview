// Fill out your copyright notice in the Description page of Project Settings.

#include "CPPPlayerPawn.h"
#include "CPPPlayerShip.h"

ACPPPlayerPawn::ACPPPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	//SceneComponent->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 10.0f;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	//Rotate camera
	FRotator CameraRotation = FRotator(0.0f, 0.0f, 90.0f);
	CameraComponent->SetRelativeRotation(CameraRotation);
}

void ACPPPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnInfo;
	Ship = GetWorld()->SpawnActor<ACPPPlayerShip>(ACPPPlayerShip::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
	Ship->SetActorScale3D(FVector(0.05f, 0.05f, 0.05f));
}

void ACPPPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
