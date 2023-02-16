// Copyright TimeLine Studio. All Rights Reserved.


#include "UserInterface/DarenSlotHolder.h"
#include "MathUtil.h"
#include <Components/CanvasPanelSlot.h>

TArray<FVector2D> UDarenSlotHolder::CalculateSlotPositions(TArray<UUserWidget*> Slots, float Radius, UUserWidget* Container)
{
	auto Step = (PI * 2) / Slots.Num();
	UCanvasPanelSlot* ContainerAsSlot = Cast<UCanvasPanelSlot>(Container->Slot);
	auto ContainerPosition = ContainerAsSlot->GetPosition();
	TArray<FVector2D> SlotsPositions;
	for (auto i = 1; i < (Slots.Num() + 1); i++)
	{
		auto Angle = Step * i;
		auto PosX = FMath::Cos(Angle + 8.9f) * Radius;
		auto PosY = FMath::Sin(Angle + 8.9f) * Radius;
		auto Pos = FVector2D(PosX, PosY);
		SlotsPositions.Add(ContainerPosition + Pos);
	}
	return SlotsPositions;
}
