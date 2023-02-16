// Copyright TimeLine Studio. All Rights Reserved.


#include "NPC/Tasks/DarenEndDialogueNode.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Character/DarenCharacter.h"
#include "Character/DarenPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NPC/DarenAIController.h"
#include "UserInterface/DarenDialogueBoxWidget.h"

UDarenEndDialogueNode::UDarenEndDialogueNode()
{
	NodeName = "End Dialogue";
}

EBTNodeResult::Type UDarenEndDialogueNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	auto DialogueBox = Cast<UDarenDialogueBoxWidget>(Blackboard->GetValueAsObject(DialogueUIElementKey.SelectedKeyName));
	DialogueBox->DialogueExit();
	const auto AIController = Cast<ADarenAIController>(OwnerComp.GetAIOwner());
	AIController->EndAction();
	const auto PlayerCharacter  = Cast<ADarenCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	PlayerCharacter->bIsInAction = false;
	const auto PlayerController = Cast<ADarenPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->SetViewTargetWithBlend(PlayerCharacter, 1);
	return EBTNodeResult::Succeeded;

}
