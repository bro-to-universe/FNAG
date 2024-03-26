// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelConfig.h"
#include "LevelConfigFactory.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class FNAG_API ULevelConfigFactory : public UObject
{
	GENERATED_BODY()

public:
	~ULevelConfigFactory();
	ULevelConfigFactory();

	ULevelConfig* GetLevelConfig(int LevelNumber);

	void UpdateCustomNightConfig(int Van, int Ricardo, int Billy, int MarkWolf, int Fernando);

private:

	ULevelConfig* CreateLevelConfig(int Van, int Ricardo, int Billy, int MarkWolf, int Fernando);

	TArray<ULevelConfig*> Configs;
};
