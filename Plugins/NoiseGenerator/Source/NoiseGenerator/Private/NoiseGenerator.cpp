// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoiseGenerator.h"
#include "NoiseGeneratorStyle.h"
#include "NoiseGeneratorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName NoiseGeneratorTabName("NoiseGenerator");

#define LOCTEXT_NAMESPACE "FNoiseGeneratorModule"

void FNoiseGeneratorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FNoiseGeneratorStyle::Initialize();
	FNoiseGeneratorStyle::ReloadTextures();

	FNoiseGeneratorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FNoiseGeneratorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FNoiseGeneratorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FNoiseGeneratorModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(NoiseGeneratorTabName, FOnSpawnTab::CreateRaw(this, &FNoiseGeneratorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FNoiseGeneratorTabTitle", "NoiseGenerator"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FNoiseGeneratorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FNoiseGeneratorStyle::Shutdown();

	FNoiseGeneratorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(NoiseGeneratorTabName);
}

TSharedRef<SDockTab> FNoiseGeneratorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FNoiseGeneratorModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("NoiseGenerator.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FNoiseGeneratorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(NoiseGeneratorTabName);
}

void FNoiseGeneratorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FNoiseGeneratorCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FNoiseGeneratorCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNoiseGeneratorModule, NoiseGenerator)