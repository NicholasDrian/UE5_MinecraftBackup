#pragma once
// Copyright Epic Games, Inc. All Rights Reserved.

#include "MountainsGameMode.h"
#include "MountainsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Tests.h"

AMountainsGameMode::AMountainsGameMode()
{
	Tests::RunTests();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PawnClass(TEXT("/Script/Mountains.FlyingPawn"));
	if (PawnClass.Class != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Flying Pawn Class Created"));
		DefaultPawnClass = PawnClass.Class;
	}
}
