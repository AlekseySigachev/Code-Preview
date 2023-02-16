// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DarenMoveToNode.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenMoveToNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UDarenMoveToNode();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector TargetKey;
};
