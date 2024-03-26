// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashLightComponent.h"

// Sets default values for this component's properties
UFlashLightComponent::UFlashLightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UFlashLightComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UFlashLightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFlashLightComponent::Init(USpotLightComponent* SpotLight)
{
	LightComponent = SpotLight;
	TurnOff();
}

void UFlashLightComponent::TurnOn()
{
	USpotLightComponent* Light = GetLightComponent();
	if (Light) {
		Light->SetIntensity(IntensityValueOn);
	}
}

void UFlashLightComponent::TurnOff()
{
	USpotLightComponent* Light = GetLightComponent();
	if (Light) {
		Light->SetIntensity(IntensityValueOff);
	}
}

USpotLightComponent* UFlashLightComponent::GetLightComponent()
{
	if (LightComponent) {
		return LightComponent;
	}
	UE_LOG(LogTemp, Error, TEXT("Tried use FlashlightComponent before Init"));
	return nullptr;
}

