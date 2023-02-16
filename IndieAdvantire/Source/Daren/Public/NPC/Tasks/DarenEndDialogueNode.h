// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DarenEndDialogueNode.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenEndDialogueNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UDarenEndDialogueNode();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Widget")
	FBlackboardKeySelector DialogueUIElementKey;
private:
};
