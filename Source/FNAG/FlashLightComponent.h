// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SpotLightComponent.h"
#include "FlashLightComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FNAG_API UFlashLightComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFlashLightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void Init(USpotLightComponent* SpotLight);

	UFUNCTION(BlueprintCallable)
		void TurnOn();

	UFUNCTION(BlueprintCallable)
		void TurnOff();

	UFUNCTION(BlueprintCallable)
		USpotLightComponent* GetLightComponent();

	USpotLightComponent* LightComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	float IntensityValueOn = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	float IntensityValueOff = 0.f;
};
