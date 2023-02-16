// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DarenHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAREN_API UDarenHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDarenHealthComponent();

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return FMath::IsNearlyZero(CurrentHealth); }

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, 
		class AController* InstigatedBy, AActor* DamageCauser);
private:
	void ApplyDamage(float Damage, AController* InstigatedBy);
public:
	void SetHealth(float Health);

public:
	float CurrentHealth;
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, DisplayName = "Character Max Health", Category = "Parametrs|Health")
	float MaxHealth = 100.0f;

private:
};