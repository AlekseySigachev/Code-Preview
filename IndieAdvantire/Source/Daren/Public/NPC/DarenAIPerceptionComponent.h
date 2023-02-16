// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "DarenAIPerceptionComponent.generated.h"

UCLASS()
class DAREN_API UDarenAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	UDarenAIPerceptionComponent();
	UFUNCTION()
	void SearchForPlayer(AActor* Actor, FAIStimulus Stimulus);
protected:

private:
	UPROPERTY(VisibleAnywhere)
	UAISenseConfig_Sight* Vision;
	
};
