// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DarenSeePlayerDecorator.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenSeePlayerDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	UDarenSeePlayerDecorator();
protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
