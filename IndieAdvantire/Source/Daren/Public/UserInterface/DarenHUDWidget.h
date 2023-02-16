// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DarenHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
protected:
private:

public:
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	class UWidgetAnimation* GameStarted;
//	UPROPERTY(meta = (BindWidget))
	class UWidgetAnimation* RenderSlots;
//	UPROPERTY(meta = (BindWidget))
	class UWidgetAnimation* Bluring;
//	UPROPERTY(meta = (BindWidget))
	class UWidgetAnimation* AliveAnimation;
//	UPROPERTY(meta = (BindWidget))
	class UWidgetAnimation* DeathAnimation;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UUserWidget* DialogueBox;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UUserWidget* EffectiveSlotHolder;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UUserWidget* MenuSlotHolder;
protected:
private:
};
