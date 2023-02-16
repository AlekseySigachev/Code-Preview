


#include "Map/CPPScene.h"

ACPPScene::ACPPScene()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneComponent);

	SceneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Scene Mesh"));
	SceneMesh->SetupAttachment(GetRootComponent());
	SceneMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -200.0f));

	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spot Light"));
	Light->SetupAttachment(GetRootComponent());
	Light->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	Light->SetRelativeRotation(FRotator(-90.0f, 180.f, 180.0f));
	Light->Intensity = 16000.0f;
	Light->OuterConeAngle = 25.0f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/ProjectS/StaticMesh/SM_SceneBox"));
	if (Mesh.Succeeded()) 
	{
		UStaticMesh* SM_Scene = Mesh.Object;

		SceneMesh->SetStaticMesh(SM_Scene);
	}
}
