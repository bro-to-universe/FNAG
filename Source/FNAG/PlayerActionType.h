// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "PlayerActionType.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum EPlayerActionType : uint8
{
	Seating UMETA(DisplayName = "Seating"),
	Standing UMETA(DisplayName = "Standing"),
	CheckingSecurityCameras UMETA(DisplayName = "CheckingSecurityCameras"),
	ForceRotating UMETA(DisplayName = "ForceRotating"),
	Moving UMETA(DisplayName = "Moving"),
	LeftDoorStanding UMETA(DisplayName = "LeftDoorStanding"),
	LeftDoorClosing UMETA(DisplayName = "LeftDoorClosing"),
	RightDoorStanding UMETA(DisplayName = "RightDoorStanding"),
	RightDoorClosing UMETA(DisplayName = "RightDoorClosing"),
	TrainingBarStanding UMETA(DisplayName = "TrainingBarStanding"),
	SeatingFlashLight UMETA(DisplayName = "SeatingFlashLight"),
	StandingFlashLight UMETA(DisplayName = "StandingFlashLight"),
	MAX UMETA(Hidden)
};
