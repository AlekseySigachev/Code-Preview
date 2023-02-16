// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCPP.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATestCPP::ATestCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestCPP::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATestCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

