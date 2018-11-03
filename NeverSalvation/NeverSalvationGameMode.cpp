// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "NeverSalvationGameMode.h"
#include "NeverSalvationCharacter.h"

ANeverSalvationGameMode::ANeverSalvationGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ANeverSalvationCharacter::StaticClass();	
}
