// Fill out your copyright notice in the Description page of Project Settings.


#include "BFL_NoiseGenerator.h"

#include "WidgetBlueprint.h"
#include "LevelEditor.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "IBlutilityModule.h"
#include "EditorUtilityWidgetBlueprint.h"


void UBFL_NoiseGenerator::StartWidget(UWidgetBlueprint* Blueprint)
{
	if(Blueprint->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
	{
		const UEditorUtilityWidget* CDO = Cast<const UEditorUtilityWidget>(Blueprint->GeneratedClass->GetDefaultObject());
		if(CDO->ShouldAutoRunDefaultAction())
		{
			//This is an instant-run blueprint, just execute it
			UEditorUtilityWidget* Instance = NewObject<UEditorUtilityWidget>(Blueprint->GeneratedClass);
			Instance->ExecuteDefaultAction();
		}
		else
		{
			FName RegistrationName = FName(*(Blueprint->GetPathName() + TEXT("_ActiveTab")));
			FText DisplayName = FText::FromString(Blueprint->GetName());
			FLevelEditorModule& LevelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
			TSharedPtr LevelEditorTabManager = LevelEditor.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(RegistrationName, false);
		}
	}
}
