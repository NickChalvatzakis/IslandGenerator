// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "NoiseGeneratorStyle.h"

class FNoiseGeneratorCommands : public TCommands<FNoiseGeneratorCommands>
{
public:

	FNoiseGeneratorCommands()
		: TCommands<FNoiseGeneratorCommands>(TEXT("NoiseGenerator"), NSLOCTEXT("Contexts", "NoiseGenerator", "NoiseGenerator Plugin"), NAME_None, FNoiseGeneratorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};