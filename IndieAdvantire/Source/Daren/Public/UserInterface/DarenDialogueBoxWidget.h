// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Overlay.h"
#include "DarenDialogueBoxWidget.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API UDarenDialogueBoxWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	class UWidgetAnimation* Show;
	void SetSpeakerName(const FText Name ) { SpeakerName = Name; }
	void SetDialogueText(const FText Text ) { DialogueText = Text; }

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UOverlay* ResponseListPanel;

	void OnShowDialogue();
	void DialogueExit();
	void OnHideDialogue();
protected:
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	FText DialogueText;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	FText SpeakerName;
	FTimerHandle WaitAnimation;
};
