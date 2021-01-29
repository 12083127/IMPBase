// Copyright Epic Games, Inc. All Rights Reserved.

#include "IMPBaseGameMode.h"
#include "Player/IMPPlayer.h"
#include "UObject/ConstructorHelpers.h"

AIMPBaseGameMode::AIMPBaseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/DemoContent/Player/BP_IMPPlayer"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
