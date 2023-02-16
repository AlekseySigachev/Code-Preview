// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "DarenIsInRadiusDecorator.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenIsInRadiusDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	UDarenIsInRadiusDecorator();
protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
