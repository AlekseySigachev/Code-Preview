

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CPPHUDWidget.generated.h"

class ACPPMainGameMode;

/**
 * 
 */
UCLASS()
class MAPSTEPTEST_API UCPPHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* EndTurnButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* GoInside;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* GoOutside;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* Move;
	UPROPERTY(BlueprintReadWrite, Category = "Main|Set UP")
		ACPPMainGameMode* GameMode;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
		void OnEndTurnButtonClicked();
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
		void OnGoInsideButtonClicked();
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
		void OnGoOutSideButtonClicked();
	UFUNCTION(BlueprintCallable, Category = "Main|Functions")
		void OnMoveButtonClicked();
};
