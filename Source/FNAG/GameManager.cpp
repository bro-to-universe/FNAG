// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

void UGameManager::Init()
{
	GameData = Cast<UGameData>(UGameplayStatics::LoadGameFromSlot(SlotGameData, 0));

	if (!GameData) {
		GameData = Cast<UGameData>(UGameplayStatics::CreateSaveGameObject(UGameData::StaticClass()));
		SaveGameData(1);
	}
}

UGameManager::UGameManager() {
	Init();
}

void UGameManager::SaveGameData(int LevelNumber)
{
	if (GameData) {
		GameData->CurrentLevelNumber = LevelNumber;
		UGameplayStatics::SaveGameToSlot(GameData, SlotGameData, 0);
	}
}

UGameData* UGameManager::LoadGameData()
{
	if (GameData) {
		return GameData;
	}
	else {
		Init();
		return GameData;
	}
}

int UGameManager::LoadCurrentLevelNumber()
{
	UGameData* Data = LoadGameData();
	return Data->CurrentLevelNumber;
}
