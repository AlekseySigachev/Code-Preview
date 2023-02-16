// Aleksey Sigachev. All Right Reserved.


#include "AI/EQS/EnvQueryTest_PickUpCouldBeTaken.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/STUBasePickup.h"

UEnvQueryTest_PickUpCouldBeTaken::UEnvQueryTest_PickUpCouldBeTaken(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickUpCouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
	const auto DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);
	
	bool bWantsBeTaken = BoolValue.GetValue();
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());
		const auto PickUpActor = Cast<ASTUBasePickup>(ItemActor);
		if(!PickUpActor) continue;
		const auto CouldBeTaken = PickUpActor->CouldBeTaken();
		It.SetScore(TestPurpose, FilterType, CouldBeTaken, bWantsBeTaken);
	}
}

