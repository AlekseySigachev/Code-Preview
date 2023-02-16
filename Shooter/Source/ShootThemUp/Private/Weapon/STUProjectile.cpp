// Aleksey Sigachev. All Right Reserved.


#include "Weapon/STUProjectile.h"

#include "AudioDevice.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/STUWeaponFXComponent.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->bReturnMaterialOnMove = true;

	SetRootComponent(CollisionComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>
		(TEXT("ProjectileMovementComponent"));
	
	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponFXComponent);
	check(ProjectileMovementComponent)
	check(CollisionComponent)
	ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
	//SetLifeSpan(LifeSeconds);
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;
	ProjectileMovementComponent->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		DamageAmount,
		GetActorLocation(),
		DamageRadius, UDamageType::StaticClass(),
		{GetOwner()},
		this,
		GetController(),
		DoFullDamage);

	//DrawDebugSphere(GetWorld(),GetActorLocation(),DamageRadius,24,FColor::Red,false,LifeSeconds);
	WeaponFXComponent->PlayImpactFX(Hit);

	Destroy();
}

AController* ASTUProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}
