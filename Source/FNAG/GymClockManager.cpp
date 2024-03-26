// Fill out your copyright notice in the Description page of Project Settings.


#include "GymClockManager.h"

// Sets default values for this component's properties
UGymClockManager::UGymClockManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UGymClockManager::BeginPlay()
{
	Super::BeginPlay();
}

//void UGymClockManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
//{
//	ClearTimers();
//}

void UGymClockManager::LaunchTimer(int LevelNumber)
{
	TimeToChangeHour = 48.f + (LevelNumber * 2.f);

	TriggerClockTimer();
}

void UGymClockManager::HourIncrement()
{
	if (Hour < 6) {
		Hour++;
		OnHourLeft.Broadcast(Hour);
		TriggerClockTimer();
	}
	else {
		ClearTimers();
	}
}

void UGymClockManager::ClearTimers() {
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void UGymClockManager::TriggerClockTimer()
{
	GetWorld()->GetTimerManager().SetTimer(ClockTimerHandler, this, &UGymClockManager::HourIncrement, TimeToChangeHour, false);
}
