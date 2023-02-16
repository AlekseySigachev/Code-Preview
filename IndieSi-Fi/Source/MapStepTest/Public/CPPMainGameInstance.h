

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CPPMainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MAPSTEPTEST_API UCPPMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Main|Set UP")
	int32 PlayersQuantity = 4;
};
