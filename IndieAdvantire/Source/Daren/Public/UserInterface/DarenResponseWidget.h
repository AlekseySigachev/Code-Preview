// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "DarenResponseWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResponse, FText, Response);

UCLASS()
class DAREN_API UDarenResponseWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnResponseClicked();
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ResponseButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FText Text;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ResponseText;

	UPROPERTY(BlueprintAssignable)
	FOnResponse OnResponse;
};
