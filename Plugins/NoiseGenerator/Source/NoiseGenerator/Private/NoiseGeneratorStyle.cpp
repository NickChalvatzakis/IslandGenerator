// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoiseGeneratorStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FNoiseGeneratorStyle::StyleInstance = nullptr;

void FNoiseGeneratorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FNoiseGeneratorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FNoiseGeneratorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("NoiseGeneratorStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FNoiseGeneratorStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("NoiseGeneratorStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("NoiseGenerator")->GetBaseDir() / TEXT("Resources"));

	Style->Set("NoiseGenerator.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FNoiseGeneratorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FNoiseGeneratorStyle::Get()
{
	return *StyleInstance;
}
