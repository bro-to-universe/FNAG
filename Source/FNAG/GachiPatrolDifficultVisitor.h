// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GachiPatrolVisitor.h"
#include "GachiPatrolDifficultVisitor.generated.h"

/**
 *
 */
UCLASS()
class FNAG_API UGachiPatrolDifficultVisitor : public UGachiPatrolVisitor
{
	GENERATED_BODY()

public:
	UGachiPatrolDifficultVisitor();

	void SetDifficultNumber(int Value);

	virtual void VisitGachiPatrol(FGachiPosition& Position) override;

private:
	int DifficultNumber = 10;
	const float Coeficent = 0.1f;
	const int MinDifficultNumber = 0;
	const int MaxDifficultNumber = 20;

};
