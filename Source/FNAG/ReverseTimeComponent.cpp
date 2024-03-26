// Fill out your copyright notice in the Description page of Project Settings.


#include "ReverseTimeComponent.h"

// Sets default values for this component's properties
UReverseTimeComponent::UReverseTimeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UReverseTimeComponent::BeginPlay()
{
	Super::BeginPlay();

	// To get world
	AGymGameModeBase* GameMode = Cast<AGymGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode) {
		GymTimeManager = GameMode->GetGymTimeManager();
	}

	if (!GymTimeManager) {
		UE_LOG(LogTemp, Warning, TEXT("Actor \"%s\" failed to receive global time manager!"), *GetName());
	}
}


// Called every frame
void UReverseTimeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

