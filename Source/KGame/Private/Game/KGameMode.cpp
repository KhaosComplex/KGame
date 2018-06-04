// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "KGameMode.h"
#include "KCharacter.h"
#include "UObject/ConstructorHelpers.h"

AKGameMode::AKGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player/CharacterBase"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
