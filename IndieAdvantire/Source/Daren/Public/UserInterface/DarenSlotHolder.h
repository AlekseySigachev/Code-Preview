// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DarenSlotHolder.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenSlotHolder : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	TArray<FVector2D> CalculateSlotPositions(TArray<UUserWidget*> Slots, float Radius, UUserWidget* Container);
};
