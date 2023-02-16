// Copyright TimeLine Studio. All Rights Reserved.


#include "NPC/DarenAIPerceptionComponent.h"
#include "Character/DarenCharacter.h"
#include "NPC/DarenAIController.h"
#include "NPC/DarenNPCBase.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"

UDarenAIPerceptionComponent::UDarenAIPerceptionComponent()
{
	OnTargetPerceptionUpdated.AddDynamic(this, &UDarenAIPerceptionComponent::SearchForPlayer);
	Vision = CreateDefaultSubobject<UAISenseConfig_Sight>("Vision");
	SensesConfig.Add(Vision);
	Vision->DetectionByAffiliation.bDetectEnemies = true;
	Vision->DetectionByAffiliation.bDetectFriendlies = true;
	Vision->DetectionByAffiliation.bDetectNeutrals = true;
}

void UDarenAIPerceptionComponent::SearchForPlayer(AActor* Actor, FAIStimulus Stimulus)
{
	const auto Controller = Cast<ADarenAIController>(GetOwner());
	if (Stimulus.WasSuccessfullySensed())
	{
		TArray<AActor*> Actors;
		GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), Actors);
		if (Actors.Num() == 0) return;
		for (const auto Target : Actors)
		{
			if (Target->IsA(ADarenCharacter::StaticClass()))
			{
				Controller->bSeePlayer = true;
				Controller->OnSeePlayer();
				return;
			}
		}
	}
	else
	{
		Controller->bSeePlayer = false;
	}
}
