// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DarenStartDialogueTask.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenStartDialogueTask : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UDarenStartDialogueTask();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Widget")
	FBlackboardKeySelector DialogueUIElementKey;
private:
};
