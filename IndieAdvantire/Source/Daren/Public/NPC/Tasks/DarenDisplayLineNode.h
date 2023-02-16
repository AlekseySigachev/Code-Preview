// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DarenDisplayLineNode.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenDisplayLineNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UDarenDisplayLineNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector DialogueUIElementKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Text to display")
	FText DisplayText;
private:
};
