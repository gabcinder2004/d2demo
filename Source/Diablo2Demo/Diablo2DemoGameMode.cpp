// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Diablo2DemoGameMode.h"
#include "Diablo2DemoPlayerController.h"
#include "Diablo2DemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADiablo2DemoGameMode::ADiablo2DemoGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADiablo2DemoPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}