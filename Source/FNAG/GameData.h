// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameData.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class FNAG_API UGameData : public USaveGame
{
	GENERATED_BODY()

public:
	UGameData();
	~UGameData();

	UPROPERTY(BlueprintReadOnly);
	int CurrentLevelNumber = 1;

};
