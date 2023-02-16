


#include "UserInterface/CPPHUDWidget.h"
#include "CPPMainGameMode.h"
#include "Kismet/GameplayStatics.h"

void UCPPHUDWidget::NativeConstruct()
{
	GameMode = Cast<ACPPMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	EndTurnButton->OnClicked.AddDynamic(this, &UCPPHUDWidget::OnEndTurnButtonClicked);
	GoInside->OnClicked.AddDynamic(this, &UCPPHUDWidget::OnGoInsideButtonClicked);
	GoOutside->OnClicked.AddDynamic(this, &UCPPHUDWidget::OnGoOutSideButtonClicked);
	Move->OnClicked.AddDynamic(this, &UCPPHUDWidget::OnMoveButtonClicked);
}

void UCPPHUDWidget::OnEndTurnButtonClicked()
{
	GameMode->PossessNextPlayer();
}

void UCPPHUDWidget::OnGoInsideButtonClicked()
{
	UE_LOG(LogTemp, Error, TEXT("Go inside Clicked"));
}

void UCPPHUDWidget::OnGoOutSideButtonClicked()
{
	UE_LOG(LogTemp, Error, TEXT("Go outside Clicked"));
}

void UCPPHUDWidget::OnMoveButtonClicked()
{
	GameMode->MoveShipToLocation();
}
