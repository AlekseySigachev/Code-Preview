// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DarenGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	bool IsFPSShow;
};
