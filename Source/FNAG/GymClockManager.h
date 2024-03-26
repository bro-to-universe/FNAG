// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GymClockManager.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHourLeftSignature, int, hour);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FNAG_API UGymClockManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGymClockManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called when the game ends
	// virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Notify when hour left
	UPROPERTY(BlueprintAssignable)
		FOnHourLeftSignature OnHourLeft;

	// Set time to change hour
	UFUNCTION(BlueprintCallable)
		void LaunchTimer(int LevelNumber);

	// Increment hour on 1 ++
	void HourIncrement();

	// Clear all timers in world
	void ClearTimers();

	// Trigger timer 
	UFUNCTION(BlueprintCallable)
		void TriggerClockTimer();

	// Time that need for increment hour
	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	float TimeToChangeHour = 0.f;

private:

	FTimerHandle ClockTimerHandler;

	int Hour = 0;
};
