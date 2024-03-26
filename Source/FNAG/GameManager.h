// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameData.h"
#include "GameManager.generated.h"

/**
 *
 */
UCLASS()
class FNAG_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

public:
	UGameManager();
	void Init() override;

	FString SlotGameData = FString("GameData");

	UPROPERTY()
	UGameData* GameData;

	UFUNCTION(BlueprintCallable)
		void SaveGameData(int LevelNumber);

	UFUNCTION(BlueprintCallable)
		UGameData* LoadGameData();

	UFUNCTION(BlueprintCallable)
	int LoadCurrentLevelNumber();
};
