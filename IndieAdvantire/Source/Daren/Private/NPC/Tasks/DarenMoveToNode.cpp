// Copyright TimeLine Studio. All Rights Reserved.


#include "NPC/Tasks/DarenMoveToNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC/DarenAIController.h"

UDarenMoveToNode::UDarenMoveToNode()
{
	NodeName = "Move";
}

EBTNodeResult::Type UDarenMoveToNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	auto AIController = Cast<ADarenAIController>(OwnerComp.GetAIOwner());
	auto Location = Blackboard->GetValueAsVector(TargetKey.SelectedKeyName);
	AIController->MoveToLocation(Location, 50.0f);
	return EBTNodeResult::Succeeded;
}
