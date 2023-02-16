// Aleksey Sigachev. All Right Reserved.


#include "AI/STUAICharacter.h"

#include "AI/STUAIController.h"
#include "BrainComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjInit)
	:Super(ObjInit.SetDefaultSubobjectClass<USTUWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASTUAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void ASTUAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto STUAIController = Cast<AAIController>(Controller);
	if (STUAIController && STUAIController->BrainComponent)
	{
		STUAIController->BrainComponent->Cleanup();
	}
}
