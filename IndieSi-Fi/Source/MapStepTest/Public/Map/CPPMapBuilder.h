// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPSpaceObject.h"
#include "GameFramework/Actor.h"
#include "MapStepTest/CustomStructs.h"
#include "CPPMapBuilder.generated.h"

UCLASS()
class MAPSTEPTEST_API ACPPMapBuilder : public AActor
{
	GENERATED_BODY()
	
	// Variables
public:
	
protected:
private:
	UPROPERTY()
	TMap<FVector2D, ACPPSpaceObject*> MaseDict;
	UPROPERTY()
	TArray<ACPPSpaceObject*> DiscoveryHistory;
	UPROPERTY()
	UDataTable* DataTable;
	UPROPERTY()
	TArray<FName> StarsName;
	//Methods
	
public:	
	ACPPMapBuilder();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, DisplayName = "Add Start Station", Category = "Main|Functions")
	void AddStartStation(int32 Direction, int32 PosX, int32 PosY, FName Name);
	FStarsStruct* PopRandomStar();
	UFUNCTION(BlueprintCallable, DisplayName = "Discover Star", Category = "Main|Functions")
	void DiscoverStar(FVector2D key);
	UFUNCTION(BlueprintCallable, DisplayName = "Add Key And History", Category = "Main|Functions")
	void AddKeyAndHistory(ACPPSpaceObject* Object, FVector2D Key);
	UFUNCTION(BlueprintCallable, DisplayName = "Create Undiscovered Star", Category = "Main|Functions")
	void CreateUndiscoveredStars(TArray<int32> AllowDirectionList, FVector2D Coords);
	UFUNCTION(BlueprintCallable, DisplayName = "Delete Undiscovered Star", Category = "Main|Functions")
	void DeleteUndiscoveredStars(TArray<ACPPSpaceObject*> Stars);
	UFUNCTION(BlueprintCallable, DisplayName = "Clean Unused Arrows", Category = "Main|Functions")
	void CleanUnusedArrows();
	UFUNCTION(BlueprintCallable, DisplayName = "Calculate New Delta", Category = "Main|Functions")
	FVector2D CalcNewDelta(int32 Direction);
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
	bool IsEmpty(TArray<FName> Array);
	//Setters and Getters
	//MaseDict
	UFUNCTION(BlueprintCallable, Category = "Main|Setters")
	FORCEINLINE void SetMaseDict(TMap<FVector2D, ACPPSpaceObject*> Map) { MaseDict = Map; };
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Main|Getters")
	FORCEINLINE TMap<FVector2D, ACPPSpaceObject*> GetMaseDict() { return MaseDict; };

	//StarsName
	UFUNCTION(BlueprintCallable, Category = "Main|Setters")
	FORCEINLINE void SetStarsName(TArray<FName> Array) { StarsName = Array; };
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Main|Getters")
	FORCEINLINE TArray<FName> GetStarsName() { return StarsName; };
	//DiscoveryHistory
	UFUNCTION(BlueprintCallable, Category = "Main|Setters")
	FORCEINLINE void SetDiscoveryHistory(TArray<ACPPSpaceObject*> Array) { DiscoveryHistory = Array; };
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Main|Getters")
	FORCEINLINE TArray<ACPPSpaceObject*> GetDiscoveryHistory() { return DiscoveryHistory; };
	//DataTable
	UFUNCTION(BlueprintCallable, Category = "Main|Setters")
	FORCEINLINE void SetDataTable(UDataTable* Table) { DataTable = Table; };
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Main|Getters")
	FORCEINLINE UDataTable* GetDataTable() { return DataTable; };

protected:


private:
	UFUNCTION()
	void Finished();
};
