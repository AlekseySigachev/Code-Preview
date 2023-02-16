// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "DarenResponseDecorator.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenResponseDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	UDarenResponseDecorator();
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Response from player")
	FBlackboardKeySelector ResponseKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Response to check")
	FString Response;
private:
};
