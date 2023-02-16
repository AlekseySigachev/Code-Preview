// Copyright TimeLine Studio. All Rights Reserved.


#include "UserInterface/DarenGreetingWidget.h"

#include "Components/TextBlock.h"

void UDarenGreetingWidget::SetGreetingText(FString Text)
{
	Greetings->SetText(FText::FromString(Text));
}
