// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Interfaces/DarenGreetingInterface.h"
#include "DarenAIController.generated.h"

class UDarenAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class DAREN_API ADarenAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADarenAIController();
	void OnSeePlayer();
	void StartAction(UBehaviorTree* BehaviorTree);
	void EndAction();
	void StopLogic();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	void SenseConfig();

private:

	
public:
	UPROPERTY()
	bool bSeePlayer;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UDarenAIPerceptionComponent* DarenAIPerceptionComponent;
	IDarenGreetingInterface* GreetingInterface = nullptr;
	
private:
};
