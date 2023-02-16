// Aleksey Sigachev. All Right Reserved.


#include "Pickups/STUAmmoPickup.h"
#include "Components/STUWeaponComponent.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

void ASTUAmmoPickup::BeginPlay()
{
	Super::BeginPlay();
}

bool ASTUAmmoPickup::GivePickUpTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;
	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(PlayerPawn);
	if(!WeaponComponent) return false;

	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
	
	UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was taken"));
	return true;
}

void ASTUAmmoPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
