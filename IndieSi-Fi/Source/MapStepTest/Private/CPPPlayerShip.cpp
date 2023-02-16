
#include "CPPPlayerShip.h"

ACPPPlayerShip::ACPPPlayerShip()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	//SceneComponent->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Game/ProjectS/StaticMesh/B2_Mesh"));
	UStaticMesh* SM_Ship = SM.Object;
	if (SM.Succeeded()) 
	{
		ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CentralObject"));
		ShipMesh->SetupAttachment(GetRootComponent());
		ShipMesh->SetStaticMesh(SM_Ship);
	}
}


