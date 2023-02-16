// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DarenFindPatrolPointNode.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenFindPatrolPointNode : public UBTTaskNode
{
	GENERATED_BODY()
	UDarenFindPatrolPointNode();
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector PatrolPointKey;
};
