// Copyright TimeLine Studio. All Rights Reserved.


#include "UserInterface/DarenResponseWidget.h"


void UDarenResponseWidget::NativeConstruct()
{
	ResponseButton->OnClicked.AddDynamic(this, &UDarenResponseWidget::OnResponseClicked);
}

void UDarenResponseWidget::OnResponseClicked() 
{
	OnResponse.Broadcast(Text);
}
