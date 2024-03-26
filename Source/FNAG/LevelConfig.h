// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelConfig.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class FNAG_API ULevelConfig : public UObject
{
	GENERATED_BODY()

public:
	ULevelConfig();
	~ULevelConfig();

	UPROPERTY(BlueprintReadOnly)
		int VanDifficult = 0;
	UPROPERTY(BlueprintReadOnly)
		int RicardoDifficult = 0;
	UPROPERTY(BlueprintReadOnly)
		int BillyDifficult = 0;
	UPROPERTY(BlueprintReadOnly)
		int MarkWolfDifficult = 0;
	UPROPERTY(BlueprintReadOnly)
		int FernandoDifficult = 0;

	void Init(int Van, int Ricardo, int Billy, int MarkWolf, int Fernando);
	bool Compare(ULevelConfig* const LC2);
};
