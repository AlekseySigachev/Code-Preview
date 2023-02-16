// Copyright TimeLine Studio. All Rights Reserved.


#include "NPC/Tasks/DarenAttackNode.h"
#include "AIController.h"
#include "Interfaces/DarenAttackInterface.h"

UDarenAttackNode::UDarenAttackNode()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UDarenAttackNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto AIPawn = Cast<IDarenAttackInterface>(OwnerComp.GetAIOwner()->GetPawn());
	AIPawn->OnAttack();
	return EBTNodeResult::Succeeded;
}
