// Copyright TimeLine Studio. All Rights Reserved.


#include "NPC/Tasks/DarenDisplayLineNode.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NPC/DarenNPCBase.h"
#include "UserInterface/DarenDialogueBoxWidget.h"

UDarenDisplayLineNode::UDarenDisplayLineNode()
{
	NodeName = "Display Line";
	bNotifyTick = true;
}

void UDarenDisplayLineNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(Controller->WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

EBTNodeResult::Type UDarenDisplayLineNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	auto DialogueBox = Cast<UDarenDialogueBoxWidget>(Blackboard->GetValueAsObject(DialogueUIElementKey.SelectedKeyName));
	const auto AIPawn = Cast<ADarenNPCBase>(OwnerComp.GetAIOwner()->GetPawn());  
	DialogueBox->SetSpeakerName(FText::FromString(AIPawn->Name));   
	DialogueBox->SetDialogueText(DisplayText);
	return EBTNodeResult::InProgress;
}


