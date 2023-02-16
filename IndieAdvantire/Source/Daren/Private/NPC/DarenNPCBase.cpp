// Copyright TimeLine Studio. All Rights Reserved.


#include "NPC/DarenNPCBase.h"

#include "GameplayTask.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "NPC/DarenAIController.h"
#include "NavigationSystem.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UserInterface/DarenGreetingWidget.h"
#include "Daren/Public/Character/DarenCharacter.h"

//#include <NavMesh/RecastQueryFilter.h>

DEFINE_LOG_CATEGORY_STATIC(LogNPC, All, All);
ADarenNPCBase::ADarenNPCBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ADarenAIController::StaticClass();

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArmComponent);
	GreetingWidget = CreateDefaultSubobject<UWidgetComponent>("Greeting Widget");
	GreetingWidget->SetupAttachment(GetRootComponent());
	HealthComponent = CreateDefaultSubobject<UDarenHealthComponent>("HealthComponent");
	DamageSphere = CreateDefaultSubobject<USphereComponent>("DamageSphere");
	DamageSphere->SetupAttachment(GetMesh());

	//Set Object type to "Interactables"
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	static const FName PropertyEditor("PropertyEditor");
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditor);

#define LOCTEXT_NAMESPACE "PropertySection"
	TSharedRef<FPropertySection> Section = PropertyModule.FindOrCreateSection("Character", "Parametrs", LOCTEXT("Parametrs", "Parametrs"));
	Section->AddCategory("Parametrs");
#undef LOCTEXT_NAMESPACE
	
}

void ADarenNPCBase::BeginPlay()
{
	Super::BeginPlay();
	UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	Movement->MaxWalkSpeed = WalkSpeed;
	DamageSphere->OnComponentBeginOverlap.AddDynamic(this, &ADarenNPCBase::OnBeginOverlap);
	DamageSphere->OnComponentEndOverlap.AddDynamic(this, &ADarenNPCBase::OnEndOverlap);
	Widget = Cast<UDarenGreetingWidget>(GreetingWidget->GetWidget());
	Widget->SetVisibility(ESlateVisibility::Hidden);
	AIController = Cast<ADarenAIController>(GetOwner());
	if (!AIController || !BTIdle) return;
	AIController->StartAction(BTIdle);
	UE_LOG(LogNPC, Display, TEXT("Start Behaviour: %s"), *BTIdle->GetName());
	auto Health = HealthComponent->CurrentHealth;
	UE_LOG(LogNPC, Display, TEXT("Health is now: %f"), Health);
}

void ADarenNPCBase::OnGreetings()
{
	if (!Widget || !bAvailableGreeting || Widget->IsVisible() || !bAgainGreetings ) return;
	Widget->SetGreetingText(*GetRandomGreeting());
	ShowGreetingWidget();
	GetWorldTimerManager().SetTimer(GTLifeTimer, this, &ADarenNPCBase::HideGreetingWidget, GTLifeTimerRate, false);
}

void ADarenNPCBase::OnAttack()
{
	if (!Target) return;
	UE_LOG(LogNPC, Error, TEXT("Attacking: %s"), *Target->GetName());
	FPointDamageEvent PointDamageEvent;
	Target->TakeDamage(Damage, PointDamageEvent, GetController(), this);
}

FString ADarenNPCBase::GetRandomGreeting()
{
	FString EmptyArray = "Forgot to give me some text";
	if(GTTexts.IsEmpty())
	{
		return EmptyArray;
	}
	else
	{
		FString Text = GTTexts[FMath::RandRange(0, (GTTexts.Num() - 1))];
		return Text;
	}
}

FVector ADarenNPCBase::FindPatrolPoint() 
{
	if (PatrolPoints.IsEmpty() || bRandomPatrol)
	{
		auto NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		FVector Location;
		NavSys->K2_GetRandomReachablePointInRadius(GetWorld(), GetActorLocation(), Location, RandomRoamRange);
		return Location;
		//Deprecated method 4.24
		//NavSys->GetRandomPointInNavigableRadius(GetWorld(), GetActorLocation(), RandomRoamRange);
	}
	else
	{
		AActor* PatrolPoint = PatrolPoints[PatrolPointIndex];
		if ((PatrolPoints.Num() - 1) <= PatrolPointIndex)
		{
			PatrolPointIndex = 0;
			//PatrolPoint = PatrolPoints[PatrolPointIndex];
			return PatrolPoint->GetActorLocation();
		}
		else
		{
			PatrolPointIndex = PatrolPointIndex + 1;
			return PatrolPoint->GetActorLocation();
		}
	}
}

void ADarenNPCBase::ShowGreetingWidget()
{
	Widget->SetVisibility(ESlateVisibility::Visible);
}

void ADarenNPCBase::HideGreetingWidget()
{
	bAgainGreetings = false;
	GetWorldTimerManager().SetTimer(GTAgainTimer, this, &ADarenNPCBase::SetAgainGreeting, GTAgainTimerRate, false);
	Widget->SetVisibility(ESlateVisibility::Hidden);
}

void ADarenNPCBase::SetAgainGreeting()
{
	bAgainGreetings = true;
}

void ADarenNPCBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ADarenCharacter::StaticClass())) 
	{
		Target = OtherActor;
	}
}

void ADarenNPCBase::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ADarenCharacter::StaticClass()))
	{
		Target = nullptr;
	}
}

void ADarenNPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ADarenNPCBase::GetAISightRadius()
{
	return SightRadius;
}

float ADarenNPCBase::GetAILoseSightRadius()
{
	return LoseSightRadius;
}
