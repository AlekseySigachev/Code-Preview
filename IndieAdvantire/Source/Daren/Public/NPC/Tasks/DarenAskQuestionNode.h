// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NPC/DarenAIController.h"
#include "UserInterface/DarenDialogueBoxWidget.h"
#include "UserInterface/DarenResponseListWidget.h"
#include "DarenAskQuestionNode.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenAskQuestionNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UDarenAskQuestionNode();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	void PrepareResponse();

private:
	UFUNCTION()
	void ResponseReceived(FText text);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector WidgetKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector ResponseKey;
	ADarenAIController* AIController;

	UDarenDialogueBoxWidget* DialogueWidget;
	UDarenResponseListWidget* ResponseList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ResponseListClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ResponseWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Question;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> Responses;
};
