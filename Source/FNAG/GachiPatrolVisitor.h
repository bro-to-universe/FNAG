// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GachiPosition.h"
#include "GachiPatrolVisitor.generated.h"

/**
 *
 */
UCLASS()
class FNAG_API UGachiPatrolVisitor : public UObject
{
	GENERATED_BODY()

public:
	UGachiPatrolVisitor();
	~UGachiPatrolVisitor();

	virtual void VisitGachiPatrol(FGachiPosition& Position);

};
