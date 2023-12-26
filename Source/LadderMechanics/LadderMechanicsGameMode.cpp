// Copyright Epic Games, Inc. All Rights Reserved.

#include "LadderMechanicsGameMode.h"
#include "LadderMechanicsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALadderMechanicsGameMode::ALadderMechanicsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
