// Copyright TimeLine Studio. All Rights Reserved.


#include "NPC/Tasks/DarenFollowTargetNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


UDarenFollowTargetNode::UDarenFollowTargetNode()
{
	NodeName = "Find Player";
}

EBTNodeResult::Type UDarenFollowTargetNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto Location = Player->GetActorLocation();
	Blackboard->SetValueAsVector(FollowTargetKey.SelectedKeyName, Location);
	return EBTNodeResult::Succeeded;
}
