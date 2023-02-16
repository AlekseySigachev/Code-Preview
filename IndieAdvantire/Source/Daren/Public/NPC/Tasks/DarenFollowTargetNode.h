// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DarenFollowTargetNode.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenFollowTargetNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UDarenFollowTargetNode();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector FollowTargetKey;
};
