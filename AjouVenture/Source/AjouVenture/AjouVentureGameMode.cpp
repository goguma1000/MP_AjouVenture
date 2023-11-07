// Copyright Epic Games, Inc. All Rights Reserved.

#include "AjouVentureGameMode.h"
#include "AjouVentureCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAjouVentureGameMode::AAjouVentureGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_Chito.BP_Chito_C"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
