// Copyright Epic Games, Inc. All Rights Reserved.

#include "DCIH_MultiTpsGameGameMode.h"
#include "DCIH_MultiTpsGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADCIH_MultiTpsGameGameMode::ADCIH_MultiTpsGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
