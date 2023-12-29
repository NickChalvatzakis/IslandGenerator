// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "Components/Image.h"
#include "EUW_NoiseGenerator.generated.h"

UENUM(BlueprintType)
enum class EDistanceFunctionType : uint8
{
	SquareBump,
	EuclideanSquared,
	Hyperboloid,
	SmoothMin
};

UCLASS(BlueprintType)
class NOISEGENERATOR_API UEUW_NoiseGenerator : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Island Generator |Colors")
	FColor OceanColor = FColor(17, 173, 193, 255);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Island Generator |Colors")
	FColor SandColor = FColor(247, 182, 158, 255);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Island Generator |Colors")
	FColor GrassColor = FColor(91, 179, 97, 255);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Island Generator |Colors")
	FColor ForestColor = FColor(30, 136, 129, 255);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Island Generator |Colors")
	FColor RockColor = FColor(96, 108, 129, 255);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Island Generator |Colors")
	FColor SnowColor = FColor(255, 255, 255, 255);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Island Generator | Attributes")
	float WaterLevel = 0.3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Island Generator | Attributes")
	float SandLevel = 0.5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Island Generator | Attributes")
	float GrassLevel = 0.6;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Island Generator | Attributes")
	float ForestLevel = 0.7;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Island Generator | Attributes")
	float RockLevel = 0.9;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Island Generator | Attributes")
	float SnowLevel = 0.96;

private:
	FColor GetColorBasedOnHeight(float Height);

public:
	float GenerateMask(int32 x, int32 y, int32 Width, int32 Height, float Noise, float Threshold, EDistanceFunctionType Type);
	UFUNCTION(BlueprintCallable)
	void GenerateNoise(float Frequency, float Amplitude, float Lacunarity, float Octaves, UTexture2D*& Out);
	UFUNCTION(BlueprintCallable)
	void GetImageFromTexture(UTexture2D* Texture, UImage* Image);
	UFUNCTION(BlueprintCallable)
	void GetTextureFromImage(UTexture2D*& Texture, UImage* Image);
};
