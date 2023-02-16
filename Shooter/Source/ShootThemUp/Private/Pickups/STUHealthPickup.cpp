// Aleksey Sigachev. All Right Reserved.


#include "Pickups/STUHealthPickup.h"

#include "STUUtils.h"
#include "Components/STUHealthComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

void ASTUHealthPickup::BeginPlay()
{
	Super::BeginPlay();
}

bool ASTUHealthPickup::GivePickUpTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
	if(!HealthComponent) return false;
	return HealthComponent->TryToAddHealth(HealthAmount);
}

void ASTUHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
