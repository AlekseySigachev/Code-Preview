// Copyright TimeLine Studio. All Rights Reserved.


#include "UserInterface/DarenDialogueBoxWidget.h"

void UDarenDialogueBoxWidget::OnShowDialogue()
{
	SetVisibility(ESlateVisibility::Visible);
	PlayAnimationForward(Show);
}

void UDarenDialogueBoxWidget::DialogueExit()
{
	PlayAnimationReverse(Show);
	GetWorld()->GetTimerManager().SetTimer(WaitAnimation, this,
		&UDarenDialogueBoxWidget::OnHideDialogue, Show->GetEndTime(), false);
	
}

void UDarenDialogueBoxWidget::OnHideDialogue()
{
	SetVisibility(ESlateVisibility::Hidden);
}
