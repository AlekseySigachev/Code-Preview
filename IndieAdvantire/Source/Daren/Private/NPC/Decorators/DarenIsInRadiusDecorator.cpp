// Copyright TimeLine Studio. All Rights Reserved.


#include "NPC/Decorators/DarenIsInRadiusDecorator.h"
#include "NPC/DarenNPCBase.h"
#include "AIController.h"

UDarenIsInRadiusDecorator::UDarenIsInRadiusDecorator()
{
	NodeName = "RadiusCheck";
}

bool UDarenIsInRadiusDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto AIPawn = Cast<ADarenNPCBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (AIPawn->Target) 
	{
		return true;
	}
	else
	{
		return false;
	}
}
