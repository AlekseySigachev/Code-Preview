// Copyright TimeLine Studio. All Rights Reserved.


#include "NPC/Decorators/DarenResponseDecorator.h"
#include "BehaviorTree/BlackboardComponent.h"

UDarenResponseDecorator::UDarenResponseDecorator()
{
	NodeName = "Response Check";
}

bool UDarenResponseDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	return (Blackboard->GetValueAsString(ResponseKey.SelectedKeyName) ==  Response);
}
