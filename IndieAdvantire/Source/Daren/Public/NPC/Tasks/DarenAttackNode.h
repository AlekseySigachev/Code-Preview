// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DarenAttackNode.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenAttackNode : public UBTTaskNode
{
	GENERATED_BODY()
		
public:
	UDarenAttackNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
