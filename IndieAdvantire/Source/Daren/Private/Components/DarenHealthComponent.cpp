// Copyright TimeLine Studio. All Rights Reserved.


#include "Components/DarenHealthComponent.h"

UDarenHealthComponent::UDarenHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UDarenHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	SetHealth(MaxHealth);
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UDarenHealthComponent::OnTakeAnyDamage);
	}
}

void UDarenHealthComponent::OnTakeAnyDamage(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	ApplyDamage(Damage, InstigatedBy);
}

void UDarenHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
	SetHealth(CurrentHealth - Damage);
	UE_LOG(LogTemp, Warning, TEXT("Damage is: %f, Health is now: %f"), Damage, CurrentHealth);
}

void UDarenHealthComponent::SetHealth(float NewHealth)
{
	//const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	//const auto HealthDelta = NextHealth - CurrentHealth;

	CurrentHealth = NewHealth;
	//OnHealthChanged.Broadcast(CurrentHealth, HealthDelta);
}