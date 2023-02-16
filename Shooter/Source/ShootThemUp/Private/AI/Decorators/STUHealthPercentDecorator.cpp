// Aleksey Sigachev. All Right Reserved.


#include "AI/Decorators/STUHealthPercentDecorator.h"

#include "AIController.h"
#include "Components/STUHealthComponent.h"

USTUHealthPercentDecorator::USTUHealthPercentDecorator()
{
	NodeName = "Health Percent";
}

bool USTUHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;
	const auto HealthComponent = Controller->GetPawn()->FindComponentByClass<USTUHealthComponent>();
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() <= HealthPercent; 
}
