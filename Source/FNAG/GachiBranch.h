// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GachiPosition.h"
#include "GachiBranch.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FNAG_API FGachiBranch
{
	GENERATED_BODY()

public:
	FGachiBranch();
	~FGachiBranch();

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	TArray<FGachiPosition> Positions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	bool bStartAttacking = false; 

};
