// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/DarenInteractInterface.h"
#include "UserInterface/DarenHUDWidget.h"
#include "Components/DarenHealthComponent.h"
#include "DarenCharacter.generated.h"


UCLASS(Blueprintable)
class ADarenCharacter : public ACharacter
{
	GENERATED_BODY()

public:
		
	ADarenCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	UFUNCTION(BlueprintCallable)
	void OnBoxBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);
	UFUNCTION(BlueprintCallable)
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintCallable)
	void OnInteract();
	UFUNCTION(BlueprintCallable)
	bool GetIsInAction() const;

protected:
private:

public:
	UPROPERTY(BlueprintReadWrite)
	UDarenHUDWidget* HUD;
	
	bool bIsInAction = false;
	
protected:
	UPROPERTY(BlueprintReadWrite)
	AActor* InteractableActor;

private:
	/** Top down camera */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, Category = "Interactions", DisplayName = "Interact box")
	UBoxComponent* InteractBox;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets", DisplayName = "Head Up Display")
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY(EditAnyWhere, Category = "Components", DisplayName = "Health Component")
	UDarenHealthComponent* HealthComponent;

	IDarenInteractInterface* InteractionInterface = nullptr;
};

