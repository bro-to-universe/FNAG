// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/RandomStream.h"
#include "QTEComponent.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQTEFinishedSignature, bool, IsSuccess);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FNAG_API UQTEComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UQTEComponent();
	~UQTEComponent();

	void AddEvent(FName EventName);

	FName GetEventByIndex(int Index);

	FName GenerateRandomEvent();

	FName GetStoringEvent();

	bool GetEventStoring();

	void ClearStoringEvent();

	void LaunchEvent(float Delay);

	void FinishEvent();

	void ReactEvent();

	UPROPERTY(BlueprintAssignable)
		FOnQTEFinishedSignature OnQTEFinished;

	FTimerHandle TimerHandle;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		TArray<FName> Events;

	static FName EmptyEvent;

	FName StoringEvent = EmptyEvent;

	FRandomStream RS = FRandomStream(FMath::Rand());
};
