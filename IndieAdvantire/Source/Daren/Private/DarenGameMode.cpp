// Copyright Epic Games, Inc. All Rights Reserved.

#include "DarenGameMode.h"
#include "Character/DarenPlayerController.h"
#include "Character/DarenCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADarenGameMode::ADarenGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADarenPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Daren/Blueprints/Player/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Daren/Blueprints/Player/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}