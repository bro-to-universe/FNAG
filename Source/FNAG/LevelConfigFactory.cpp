// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelConfigFactory.h"

ULevelConfigFactory::ULevelConfigFactory()
{
	CreateLevelConfig(5, 0, 0, 0, 0);
	CreateLevelConfig(5, 3, 0, 0, 3);
	CreateLevelConfig(10, 10, 0, 0, 8);
	CreateLevelConfig(12, 12, 0, 0, 12);
	CreateLevelConfig(15, 15, 0, 0, 15);
	CreateLevelConfig(0, 0, 20, 0, 0);
	CreateLevelConfig(0, 0, 0, 20, 0);

	// Custom night is last
	CreateLevelConfig(0, 0, 0, 0, 0);
}

ULevelConfigFactory::~ULevelConfigFactory()
{
	Configs.RemoveAll([](ULevelConfig* LC) {
		return true;
	});
}

ULevelConfig* ULevelConfigFactory::GetLevelConfig(int LevelNumber)
{
	int ConfigIndex = LevelNumber - 1;
	int ConfigLength = Configs.Num();
	if (ConfigIndex < ConfigLength && ConfigIndex >= 0) {
		return Configs[ConfigIndex];
	}
	return CreateLevelConfig(0, 0, 0, 0, 0);
}

void ULevelConfigFactory::UpdateCustomNightConfig(int Van, int Ricardo, int Billy, int MarkWolf, int Fernando)
{
	if (Configs.Num() > 0) {
		Configs[Configs.Num() - 1]->Init(Van, Ricardo, Billy, MarkWolf, Fernando);
	}
}

ULevelConfig* ULevelConfigFactory::CreateLevelConfig(int Van, int Ricardo, int Billy, int MarkWolf, int Fernando)
{
	ULevelConfig* LevelConfig = NewObject<ULevelConfig>();
	LevelConfig->Init(Van, Ricardo, Billy, MarkWolf, Fernando);

	Configs.Add(LevelConfig);

	return LevelConfig;
}
