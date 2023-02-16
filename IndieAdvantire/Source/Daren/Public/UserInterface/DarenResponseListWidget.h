// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DarenResponseListWidget.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenResponseListWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UVerticalBox* ResponseList;
};
