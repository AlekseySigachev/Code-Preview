// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPPlayerController.h"
#include <CPPPlayerPawn.h>

ACPPPlayerController::ACPPPlayerController()
{
	SetShowMouseCursor(true);
	bEnableClickEvents = true;
}

void ACPPPlayerController::BeginPlay()
{
	if (GetPawn()) 
	{
		auto MyPawn = Cast<ACPPPlayerPawn>(GetPawn());
		FString const PawnName = MyPawn->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Possed in pawn: %s"), *PawnName);
	}
}
