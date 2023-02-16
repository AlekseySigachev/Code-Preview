// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DarenGreetingWidget.generated.h"

UCLASS()
class DAREN_API UDarenGreetingWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetGreetingText(FString Text);
protected:

private:

public:
protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Greetings;
private:
	
};
