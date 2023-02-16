// Copyright TimeLine Studio. All Rights Reserved.


#include "NPC/Tasks/DarenAskQuestionNode.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Components/VerticalBox.h"
#include "UserInterface/DarenDialogueBoxWidget.h"
#include "UserInterface/DarenResponseWidget.h"

UDarenAskQuestionNode::UDarenAskQuestionNode()
{
	NodeName = "Ask Question";
}

EBTNodeResult::Type UDarenAskQuestionNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIController = Cast<ADarenAIController>(OwnerComp.GetOwner()); 
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	DialogueWidget = Cast<UDarenDialogueBoxWidget>(Blackboard->GetValueAsObject(WidgetKey.SelectedKeyName));
	DialogueWidget->DialogueText = Question;
	PrepareResponse();
	return EBTNodeResult::InProgress;
}

void UDarenAskQuestionNode::PrepareResponse()
{
	ResponseList = CreateWidget<UDarenResponseListWidget>(GetWorld(), ResponseListClass);
	if (!ResponseList) return;
	DialogueWidget->ResponseListPanel->AddChildToOverlay(ResponseList);
	if (!DialogueWidget) return;
	for (const auto Response : Responses)
	{
		const auto ResponseWidget = CreateWidget<UDarenResponseWidget>(GetWorld(), ResponseWidgetClass);
		if (ResponseWidget)
		{
			ResponseWidget->Text = Response;
			ResponseList->ResponseList->AddChildToVerticalBox(ResponseWidget);
			ResponseWidget->OnResponse.AddDynamic(this, &UDarenAskQuestionNode::ResponseReceived);
		}
	}
}

void UDarenAskQuestionNode::ResponseReceived(FText text)
{
	UBehaviorTreeComponent* OwnerComp = Cast<UBehaviorTreeComponent>(AIController->GetBrainComponent());
	const auto Blackboard = OwnerComp->GetBlackboardComponent();
	Blackboard->SetValueAsString(ResponseKey.SelectedKeyName, text.ToString());
	ResponseList->RemoveFromParent();
	FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
}


