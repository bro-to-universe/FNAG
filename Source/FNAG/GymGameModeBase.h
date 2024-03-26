// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GymPlayer.h"
#include "TimeManager.h"
#include "GameManager.h"
#include "LevelConfigFactory.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/GameModeBase.h"
#include "GymGameModeBase.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelCompletedSignature, bool, IsSuccess);

/**
 *
 */
UCLASS()
class FNAG_API AGymGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void InitGameState() override;

	UFUNCTION(BlueprintCallable)
		ATimeManager* GetGymTimeManager();

	UFUNCTION(BlueprintCallable)
		ULevelConfig* GetCurrentLevelGonfig();

	UFUNCTION(BlueprintCallable)
		int GetCurrentLevelNumber();

	UFUNCTION(BlueprintCallable)
		void CompleteLevelSuccess();

	UFUNCTION(BlueprintCallable)
		void CompleteLevelFailed();

	UPROPERTY(BlueprintAssignable)
		FOnLevelCompletedSignature OnLevelCompleted;

protected:
	UPROPERTY(BlueprintReadOnly);
	ATimeManager* GymTimeManager = nullptr;

private:
	UPROPERTY(NoClear, EditAnywhere);
	TSubclassOf<AGymPlayer> CustomGymPlayer = AGymPlayer::StaticClass();

	ULevelConfigFactory* LevelConfigFactory;

	UGameManager* GameManager;

	ULevelConfig* LevelConfig;

	void SetLevelConfig(ULevelConfig* Value);

	int CurrentLevelNumber = 0;

	void LoadCurrentLevel();
};
