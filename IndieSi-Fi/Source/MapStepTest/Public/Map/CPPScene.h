

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SpotLightComponent.h"
#include "CPPScene.generated.h"

UCLASS()
class MAPSTEPTEST_API ACPPScene : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPPScene();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* SceneMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USpotLightComponent* Light;
public:	

};
