// Copyright TimeLine Studio. All Rights Reserved.


#include "NPC/Tasks/DarenFindPatrolPointNode.h"
#include "AIController.h"
#include "NPC/DarenNPCBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UDarenFindPatrolPointNode::UDarenFindPatrolPointNode()
{
	NodeName = "Find Patrol Point";
}

EBTNodeResult::Type UDarenFindPatrolPointNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	auto AIPawn = Cast<ADarenNPCBase>(OwnerComp.GetAIOwner()->GetPawn());
	FVector Location = FVector::ZeroVector;
	Location = AIPawn->FindPatrolPoint();
	Blackboard->SetValueAsVector(PatrolPointKey.SelectedKeyName, Location);
	return EBTNodeResult::Succeeded;
}