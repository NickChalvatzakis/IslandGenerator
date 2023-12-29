// Fill out your copyright notice in the Description page of Project Settings.


#include "EUW_NoiseGenerator.h"
#include "SimplexNoiseBPLibrary.h"

/*
 * https://old.reddit.com/r/proceduralgeneration/comments/kaen7h/new_video_on_procedural_island_noise_generation/gfjmgen/
 * https://www.redblobgames.com/maps/terrain-from-noise/
 * https://editor.p5js.org/Nova_Studios/sketches/phm7pkppC
 * https://www.youtube.com/watch?v=bMTeCqNkId8
 */

//IMPLEMENT_SHADER_TYPE(, FRaycastingIsland, TEXT("RaycastingIsland"), TEXT("MainVS"), SF_Vertex);


FColor UEUW_NoiseGenerator::GetColorBasedOnHeight(float Height)
{
	if(Height < WaterLevel)
		return OceanColor;
	if (Height < SandLevel)
		return SandColor;
	if (Height < GrassLevel)
		return GrassColor;
	if (Height < ForestLevel)
		return ForestColor;
	if (Height < RockLevel)
		return RockColor;

	return SnowColor;
}

void UEUW_NoiseGenerator::GenerateNoise(float Frequency, float Amplitude, float Lacunarity, float Octaves,
                                         UTexture2D*& Out)
{
#if WITH_EDITOR
	const int32 Width = 600;
	const int32 Height = 600;

	Out = UTexture2D::CreateTransient(Width, Height, PF_DXT1);

	Out->Source.Init(Width, Height, /*NumSlices=*/ 1, /*NumMips=*/ 1, TSF_BGRA8);

	uint8* MipData = Out->Source.LockMip(0);

	for (int32 y = 0; y < Width; y++ )
	{
		uint8* DestPtr = &MipData[(Height - 1 - y) * Width * sizeof(FColor)];
		for (int32 x = 0; x < Height; x++ )
		{
			const float Noise = USimplexNoiseBPLibrary::GetSimplexNoise2D(x, y, Frequency, Amplitude,
			                                                              Lacunarity, Octaves, Width, Height, WaterLevel);

			const float Island = USimplexNoiseBPLibrary::GetIslandMask(x, y, Width, Height, Noise);

			const FColor CurrentColor = GetColorBasedOnHeight(Island);
			*DestPtr++ = CurrentColor.B;
			*DestPtr++ = CurrentColor.G;
			*DestPtr++ = CurrentColor.R;
			*DestPtr++ = CurrentColor.A;

		}
	}

	Out->Source.UnlockMip(0);

	Out->PostEditChange();

	Out->UpdateResource();
#else
	UE_LOG(LogImageUtils, Fatal,TEXT("ConstructTexture2D not supported on console."));
#endif

	


}

void UEUW_NoiseGenerator::GetImageFromTexture(UTexture2D* Texture, UImage* Image)
{
	Image = NewObject<UImage>(UImage::StaticClass());
	Image->SetVisibility(ESlateVisibility::Visible);

	Image->SetBrushFromTexture(Texture, true);

}

void UEUW_NoiseGenerator::GetTextureFromImage(UTexture2D*& Texture, UImage* Image)
{
	Texture->CreateTransient(Image->GetBrush().GetImageSize().X, Image->GetBrush().GetImageSize().Y,
	                         EPixelFormat::PF_DXT1, FName(TEXT("Texture")));
}

