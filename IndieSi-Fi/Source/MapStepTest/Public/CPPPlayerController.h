// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MAPSTEPTEST_API ACPPPlayerController : public APlayerController
{
	GENERATED_BODY()
	ACPPPlayerController();
	virtual void BeginPlay() override;
};
