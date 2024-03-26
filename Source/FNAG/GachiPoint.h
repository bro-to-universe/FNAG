// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "GachiPoint.generated.h"

UCLASS()
class FNAG_API AGachiPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGachiPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Return position and rotation of patrol point
	UFUNCTION(BlueprintCallable)
		void GetLocationAndRotation(FVector& Location, FRotator& Rotation);

	void VisitPoint();
	void LeftPoint();
	bool IsPointBusy();

public:
	UPROPERTY(EditAnywhere);
	UArrowComponent* PositionMesh;

private:
	// Location of patrol point
	FVector PositionLocation;

	// Rotation of patrol point 
	FRotator PositionRotation;

	// Is point busy by gachi right now
	bool IsBusy = false;
};
