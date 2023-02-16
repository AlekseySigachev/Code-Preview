// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Map/CPPScene.h>
#include "GameFramework/GameModeBase.h"
#include "CPPMainGameMode.generated.h"


class ACPPSpaceObject;
class ACPPSpaceObject_Station;
class ACPPPlayerPawn;
class ACPPPlayerController;
class UCPPHUDWidget;
/**
 * 
 */
UCLASS()
class MAPSTEPTEST_API ACPPMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	ACPPMainGameMode();

//Variables

public:
	UPROPERTY(BlueprintReadWrite, DisplayName = "PlayersREF", Category = "Main|References")
	TArray<ACPPPlayerPawn*> Players;
	UPROPERTY(BlueprintReadWrite, DisplayName = "StartStationREF", Category = "Main|References")
	ACPPSpaceObject_Station* StartStation;
	UPROPERTY(BlueprintReadWrite, DisplayName = "PlayerControllerREF", Category = "Main|References")
	ACPPPlayerController* PlayerController;
	UPROPERTY(BlueprintReadWrite, DisplayName = "CurrentPlayerREF", Category = "Main|References")
	ACPPPlayerPawn* CurrentPlayer;
	UPROPERTY(EditDefaultsOnly, Category = "Main|References")
		TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY(BlueprintReadWrite, DisplayName = "MainSceneREF", Category = "Main|References")
	ACPPScene* MainScene;
	UPROPERTY(BlueprintReadWrite, DisplayName = "SubSceneREF", Category = "Main|References")
	ACPPScene* SubScene;
	//SolarSystemBuilder
protected:
private:
	UPROPERTY(EditDefaultsOnly, DisplayName = "PlayerClass", Category = "Main|References")
		TSubclassOf<AActor> PlayerClass;
	UPROPERTY(EditDefaultsOnly, Category = "Main|References")
	UCPPHUDWidget* HUD;
	UPROPERTY(EditDefaultsOnly, DisplayName = "Delta", Category = "Main|References")
	FVector Delta = FVector(600.0f, 0.0f, 0.0f);

//Functions

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Main|Getters")
	int32 GetPlayerQuantity();
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
	void SpawnPlayers(ACPPSpaceObject_Station* Station);
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
	void MovePlayerToLocations(ACPPSpaceObject* Target);
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
	void CheckAllowedDirection(ACPPSpaceObject* PlayerStar, ACPPSpaceObject* ShipStar);
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
	int32 GetRequieredDirection(ACPPSpaceObject* PlayerStar, ACPPSpaceObject* ShipStar);
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
	int32 TopDownMove(FVector ShipLoc, FVector PlayerLoc);
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
	int32 LeftRightMove(FVector ShipLoc, FVector PlayerLoc);
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
	void OnOffMoveButton(bool Switch);
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
	void MoveShipToLocation();
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
	void PossessFirstPlayer();
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
	void PossessNextPlayer();
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
	void ReallocatePlayer();
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
	void ToggleInsideButton(ACPPSpaceObject* Target);
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
	void DrawScene();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Main|Getters")
	FORCEINLINE FVector GetDelta() { return Delta; };

protected:
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void CreateHUDWidget();
};
