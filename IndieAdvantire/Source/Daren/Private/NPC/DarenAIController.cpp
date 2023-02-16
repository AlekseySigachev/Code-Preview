// Copyright TimeLine Studio. All Rights Reserved.


#include "NPC/DarenAIController.h"

#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "NPC/DarenAIPerceptionComponent.h"
#include "NPC/DarenInteractableNPC.h"
#include "NPC/DarenNPCBase.h"
#include "Perception/AISenseConfig_Sight.h"

ADarenAIController::ADarenAIController()
{
	DarenAIPerceptionComponent = CreateDefaultSubobject<UDarenAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*DarenAIPerceptionComponent);
}

void ADarenAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ADarenAIController::BeginPlay()
{
	SenseConfig();
	Super::BeginPlay();
}

void ADarenAIController::SenseConfig()
{

	const auto NPC = Cast<ADarenNPCBase>(GetPawn());
	if(!NPC) return;
	FAISenseID SenseID = UAISense::GetSenseID<UAISense_Sight>();
	UAISenseConfig_Sight* SenseConfig = Cast<UAISenseConfig_Sight>(DarenAIPerceptionComponent->GetSenseConfig(SenseID));
	if (SenseConfig)
	{
		SenseConfig->SightRadius = NPC->GetAISightRadius();
		SenseConfig->LoseSightRadius = NPC->GetAILoseSightRadius();
		DarenAIPerceptionComponent->ConfigureSense(*SenseConfig);
	}
}

void ADarenAIController::OnSeePlayer()
{
	const auto CurrentPawn = GetPawn();
	GreetingInterface = Cast<IDarenGreetingInterface>(CurrentPawn);
	if (GreetingInterface)
	{
		GreetingInterface->OnGreetings();
	}
}

void ADarenAIController::StartAction(UBehaviorTree* BehaviorTree)
{
	GetPawn()->GetMovementComponent()->StopMovementImmediately();
	StopLogic();
	RunBehaviorTree(BehaviorTree);
}

void ADarenAIController::EndAction()
{
	GetBrainComponent()->StopLogic("End Dialogue");
	const auto NPC = Cast<ADarenInteractableNPC>(GetPawn());
	if(NPC->BTIdle)
	{
		RunBehaviorTree(NPC->BTIdle);
	} 
}

void ADarenAIController::StopLogic()
{
	if(IsValid(GetBrainComponent()))
	{
		GetBrainComponent()->StopLogic("ASas");
	}
}


