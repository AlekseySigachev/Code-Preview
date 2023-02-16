// Copyright TimeLine Studio. All Rights Reserved.


#include "NPC/DarenInteractableNPC.h"

#include "Kismet/GameplayStatics.h"
#include "NPC/DarenAIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogInteractableNPC, All, All);

ADarenInteractableNPC::ADarenInteractableNPC()
{
	
}

void ADarenInteractableNPC::OnInteract()
{
	UE_LOG(LogInteractableNPC, Display, TEXT("Player interacting with me"));
	if (!BTAction) return;
	if (!AIController) return;
	if (BTAction == BTAlarm) 
	{
		if (!BTAlarm) return;
		AIController->StartAction(BTAlarm);
	}
	else
	{
		AIController->StartAction(BTAction);
		UE_LOG(LogInteractableNPC, Display, TEXT("Start Behaviour: %s"), *BTAction->GetName());
		const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->SetViewTargetWithBlend(this, 1);
	}
}
