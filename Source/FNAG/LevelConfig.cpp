// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelConfig.h"

ULevelConfig::ULevelConfig() {

}

ULevelConfig::~ULevelConfig()
{
}

void ULevelConfig::Init(int Van, int Ricardo, int Billy, int MarkWolf, int Fernando)
{
	VanDifficult = Van;
	RicardoDifficult = Ricardo;
	BillyDifficult = Billy;
	MarkWolfDifficult = MarkWolf;
	FernandoDifficult = Fernando;
}

bool ULevelConfig::Compare(ULevelConfig* const LC2)
{
	return LC2->VanDifficult == VanDifficult && LC2->BillyDifficult == BillyDifficult && LC2->FernandoDifficult == FernandoDifficult && LC2->MarkWolfDifficult == MarkWolfDifficult && LC2->RicardoDifficult == RicardoDifficult;
}
