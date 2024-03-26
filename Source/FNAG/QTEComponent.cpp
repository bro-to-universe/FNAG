// Fill out your copyright notice in the Description page of Project Settings.


#include "QTEComponent.h"

// Sets default values for this component's properties
UQTEComponent::UQTEComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

UQTEComponent::~UQTEComponent()
{
	ClearStoringEvent();
}

FName UQTEComponent::EmptyEvent = FName("");

void UQTEComponent::AddEvent(FName EventName)
{
	Events.Add(EventName);
}

FName UQTEComponent::GetEventByIndex(int Index)
{
	if (Index >= 0 && Index < Events.Num()) {
		return Events[Index];
	}
	return EmptyEvent;
}

FName UQTEComponent::GenerateRandomEvent()
{
	ClearStoringEvent();
	int EventsLength = Events.Num();
	if (EventsLength == 0) {
		return EmptyEvent;
	}
	int NextEventIndex = RS.RandRange(0, EventsLength - 1);
	UE_LOG(LogTemp, Warning, TEXT("QTE Next event index is %d, len %d"), NextEventIndex, EventsLength);
	StoringEvent = GetEventByIndex(NextEventIndex);
	return StoringEvent;
}

FName UQTEComponent::GetStoringEvent()
{
	return StoringEvent;
}

bool UQTEComponent::GetEventStoring()
{
	return StoringEvent != EmptyEvent;
}

void UQTEComponent::ClearStoringEvent()
{
	UWorld* World = GetWorld();
	if (World) {
		World->GetTimerManager().ClearAllTimersForObject(this);
	}
	StoringEvent = EmptyEvent;
}

void UQTEComponent::LaunchEvent(float Delay)
{
	GenerateRandomEvent();
	UWorld* World = GetWorld();
	if (World) {
		World->GetTimerManager().SetTimer(TimerHandle, this, &UQTEComponent::FinishEvent, Delay, false);
	}
}

void UQTEComponent::FinishEvent() {
	ClearStoringEvent();
	OnQTEFinished.Broadcast(false);
}

void UQTEComponent::ReactEvent()
{
	ClearStoringEvent();
	OnQTEFinished.Broadcast(true);
}


// Called when the game starts
void UQTEComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UQTEComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

