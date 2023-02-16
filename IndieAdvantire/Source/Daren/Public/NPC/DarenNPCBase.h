// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/DarenGreetingInterface.h"
#include "Interfaces/DarenAttackInterface.h"
#include "Components/DarenHealthComponent.h"
#include "Components/SphereComponent.h"
#include "DarenNPCBase.generated.h"

class UWidgetComponent ;
class UDarenGreetingWidget;
class ADarenAIController;

UCLASS()
class DAREN_API ADarenNPCBase : public ACharacter, public IDarenGreetingInterface, public IDarenAttackInterface
{
	GENERATED_BODY()

public:
	ADarenNPCBase();
	
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	float GetAISightRadius();
	UFUNCTION(BlueprintCallable)
	float GetAILoseSightRadius();
	UFUNCTION(BlueprintCallable)
	virtual FVector FindPatrolPoint();
	
protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	virtual void OnGreetings() override;
	UFUNCTION(BlueprintCallable)
	virtual void OnAttack() override;
	UFUNCTION(BlueprintCallable)
	virtual FString GetRandomGreeting();
	UFUNCTION(BlueprintCallable)
	virtual void ShowGreetingWidget();
	UFUNCTION(BlueprintCallable)
	virtual void HideGreetingWidget();
	UFUNCTION(BlueprintCallable)
	virtual void SetAgainGreeting();

	UFUNCTION(BlueprintCallable)
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:


public:
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* GreetingWidget;

	UPROPERTY(EditDefaultsOnly)
	class UDarenGreetingWidget* Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs", DisplayName = "NPC's name", meta=(DisplayPriority=0))
	FString Name = "Default NPC Name";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs|Behaviour", DisplayName = "Idle Behaviour")
	UBehaviorTree* BTIdle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs|Behaviour", DisplayName = "Alarm Behaviour")
	UBehaviorTree* BTAlarm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs|Stats", DisplayName = "WalkSpeed")
	float WalkSpeed = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs|Stats", DisplayName = "Damage")
	float Damage = 20.f;
	UPROPERTY(BlueprintReadWrite, Category = "Parametrs|Attack", DisplayName = "Target")
	AActor* Target;



protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UDarenHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* DamageSphere;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs|Configuration", DisplayName = "Sight Radius")
	float SightRadius = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs|Configuration", DisplayName = "Lose Sight Radius")
	float LoseSightRadius = 200.0f;

	ADarenAIController* AIController;

	//Greetings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs", DisplayName = "Have greeting?", meta=(DisplayPriority=1))
	bool bAvailableGreeting = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs|Greetings", DisplayName = "Greeting Texts", meta=(EditCondition= "bAvailableGreeting", EditConditionHides))
	TArray<FString> GTTexts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs|Greetings", DisplayName = "Greeting Lifetime", meta=(EditCondition= "bAvailableGreeting", EditConditionHides))
	float GTLifeTimerRate = 4.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs|Greetings", DisplayName = "Reapeat Greeting", meta=(EditCondition= "bAvailableGreeting", EditConditionHides))
	float GTAgainTimerRate = 4.0f;
	UPROPERTY()
	bool bAgainGreetings  = true;

	//Patrolling
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs|Patrolling", DisplayName = "Is NPC have move behavior?")
	bool bAvailablePatrolling = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs|Patrolling", DisplayName = "Patrol Points", meta = (EditCondition = "bAvailablePatrolling", EditConditionHides))
	TArray<AActor*> PatrolPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs|Patrolling", DisplayName = "Random Patrol", meta = (EditCondition = "bAvailablePatrolling", EditConditionHides))
	bool bRandomPatrol = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs|Patrolling", DisplayName = "Random Patrol Radius", meta = (EditCondition = "bRandomPatrol", EditConditionHides))
	float RandomRoamRange = 10;

	FTimerHandle GTLifeTimer;
	FTimerHandle GTAgainTimer;
	
private:
	UPROPERTY()
	int8 PatrolPointIndex = 0;
};
