// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashLightComponentTest.h"

bool FFlashLightComponentTest::RunTest(const FString& Parameters) {
	UFlashLightComponent* FlashLight = NewObject<UFlashLightComponent>();
	USpotLightComponent* LightComponent = NewObject<USpotLightComponent>();
	FlashLight->Init(LightComponent);

	{
		TestEqual(TEXT("LightComponent's Intensity should be equal IntensityValueOff on Initialization"), LightComponent->Intensity, FlashLight->IntensityValueOff);
	}
	{
		FlashLight->TurnOn();
		TestEqual(TEXT("LightComponent's Intensity should be equal IntensityValueOn on TurnOn"), LightComponent->Intensity, FlashLight->IntensityValueOn);
	}
	{
		FlashLight->TurnOff();
		TestEqual(TEXT("LightComponent's Intensity should be equal to IntensityValueOff on TurnOff"), LightComponent->Intensity, FlashLight->IntensityValueOff);
	}

	return true;
}