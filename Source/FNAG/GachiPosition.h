// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSprite.h"
#include "GachiPoint.h"
#include "CoreMinimal.h"
#include "GachiPosition.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FNAG_API FGachiPosition
{
	GENERATED_BODY()

public:
	FGachiPosition();
	~FGachiPosition();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int PathNumber = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		AGachiPoint* Point;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<UPaperSprite*> Sprites;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<USoundBase*> Sounds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Delay = 5.f;

};
