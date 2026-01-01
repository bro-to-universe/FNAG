// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelConfigFactoryTest.h"

bool FLevelConfigFactoryTest::RunTest(const FString& Parameters)
{
	ULevelConfigFactory* LevelConfigFactory = NewObject<ULevelConfigFactory>();
	const int CustomNightLevel = 8;

	{
		ULevelConfig* LevelConfig1 = LevelConfigFactory->GetLevelConfig(1);
		ULevelConfig* const ExpectedLevelConfig1 = NewObject<ULevelConfig>();
		ExpectedLevelConfig1->Init(5, 0, 0, 0, 0);
		if (!LevelConfig1->Compare(ExpectedLevelConfig1))
		{
			AddError(TEXT("Level Config 1 isn't matched"));
		}
	}
	{
		ULevelConfig* LC = LevelConfigFactory->GetLevelConfig(CustomNightLevel);
		ULevelConfig* const ELC = NewObject<ULevelConfig>();
		ELC->Init(0, 0, 0, 0, 0);
		if (!LC->Compare(ELC)) {
			AddError(TEXT("Custom night by default should be equal to 0,0,0,0,0"));
		}
	}
	{
		LevelConfigFactory->UpdateCustomNightConfig(0, 0, 0, 15, 0);
		ULevelConfig* LC1 = LevelConfigFactory->GetLevelConfig(CustomNightLevel);
		ULevelConfig* const ELC1 = NewObject<ULevelConfig>();
		ELC1->Init(0, 0, 0, 15, 0);
		if (!LC1->Compare(ELC1)) {
			AddError(TEXT("Custom night updating doesn't work"));
		}
	}

	return true;
}
