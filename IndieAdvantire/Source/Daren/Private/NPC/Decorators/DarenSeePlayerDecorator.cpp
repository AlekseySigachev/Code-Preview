// Copyright TimeLine Studio. All Rights Reserved.


#include "NPC/Decorators/DarenSeePlayerDecorator.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC/DarenAIController.h"

UDarenSeePlayerDecorator::UDarenSeePlayerDecorator()
{
	NodeName = "IsSeePlayer";
}

bool UDarenSeePlayerDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	auto AIController = Cast<ADarenAIController>(OwnerComp.GetAIOwner());
	return AIController->bSeePlayer;
}
