// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "SecurityCamera.generated.h"

UCLASS()
class FNAG_API ASecurityCamera : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASecurityCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	bool IsBroken = false;

	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly);
	FString CameraId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	UCameraComponent* Camera;

};
