// Fill out your copyright notice in the Description page of Project Settings.


#include "GymGameModeBase.h"

void AGymGameModeBase::InitGameState()
{
	Super::InitGameState();

	LevelConfigFactory = NewObject<ULevelConfigFactory>();
	GameManager = Cast<UGameManager>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameManager) {
		UE_LOG(LogTemp, Error, TEXT("Failed to create GameManager"));
	}
	else {
		LoadCurrentLevel();
		UE_LOG(LogTemp, Warning, TEXT("Loaded level is %d"), CurrentLevelNumber);
		if (CurrentLevelNumber) {
			SetLevelConfig(LevelConfigFactory->GetLevelConfig(CurrentLevelNumber));
		}
	}

	GymTimeManager = Cast<ATimeManager>(GetWorld()->SpawnActor(ATimeManager::StaticClass()));
	if (!GymTimeManager) {
		UE_LOG(LogTemp, Error, TEXT("Failed to create GymTimeManager!"));
	}

	if (DefaultPawnClass == ADefaultPawn::StaticClass() || !DefaultPawnClass) {
		DefaultPawnClass = CustomGymPlayer;
	}
}

ATimeManager* AGymGameModeBase::GetGymTimeManager()
{
	if (!GymTimeManager) {
		UE_LOG(LogTemp, Error, TEXT("Tried to call GetGymTimeManager() before it existed"));
	}

	return GymTimeManager;
}

void AGymGameModeBase::SetLevelConfig(ULevelConfig* Value)
{
	LevelConfig = Value;
}

ULevelConfig* AGymGameModeBase::GetCurrentLevelGonfig()
{
	return LevelConfig;
}

int AGymGameModeBase::GetCurrentLevelNumber()
{
	return CurrentLevelNumber;
}

void AGymGameModeBase::CompleteLevelSuccess()
{
	GameManager->SaveGameData(CurrentLevelNumber + 1);
	OnLevelCompleted.Broadcast(true);
}

void AGymGameModeBase::CompleteLevelFailed()
{
	OnLevelCompleted.Broadcast(false);
}

void AGymGameModeBase::LoadCurrentLevel()
{
	CurrentLevelNumber = GameManager->LoadCurrentLevelNumber();
}
