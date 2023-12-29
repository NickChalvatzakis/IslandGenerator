// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EditorUtilityWidget.h"
#include "WidgetBlueprint.h"
#include "BFL_NoiseGenerator.generated.h"

/**
 * 
 */
UCLASS(BlueprintType) 
class NOISEGENERATOR_API UBFL_NoiseGenerator : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void StartWidget(UWidgetBlueprint* Blueprint);
	
};
