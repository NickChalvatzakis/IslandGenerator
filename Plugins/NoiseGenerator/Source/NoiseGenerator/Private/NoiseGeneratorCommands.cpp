// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoiseGeneratorCommands.h"

#define LOCTEXT_NAMESPACE "FNoiseGeneratorModule"

void FNoiseGeneratorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "NoiseGenerator", "Bring up NoiseGenerator window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
