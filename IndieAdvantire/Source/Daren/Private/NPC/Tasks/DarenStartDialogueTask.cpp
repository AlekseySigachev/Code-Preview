// Copyright TimeLine Studio. All Rights Reserved.


#include "NPC/Tasks/DarenStartDialogueTask.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Character/DarenCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/DarenDialogueBoxWidget.h"

UDarenStartDialogueTask::UDarenStartDialogueTask()
{
	NodeName = "Start Dialogue";
}

EBTNodeResult::Type UDarenStartDialogueTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Player = Cast<ADarenCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Player->GetIsInAction()) return EBTNodeResult::Failed;
	Player->GetCharacterMovement()->DisableMovement();
	const auto DialogueBox = Cast<UDarenDialogueBoxWidget>(Player->HUD->DialogueBox);
	DialogueBox->OnShowDialogue();
	Blackboard->SetValueAsObject(DialogueUIElementKey.SelectedKeyName, DialogueBox);
	bIgnoreRestartSelf = true;
	return EBTNodeResult::Succeeded;
}
