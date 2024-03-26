// Fill out your copyright notice in the Description page of Project Settings.


#include "GachiPatrolDifficultVisitor.h"

UGachiPatrolDifficultVisitor::UGachiPatrolDifficultVisitor()
{
}

void UGachiPatrolDifficultVisitor::SetDifficultNumber(int Value)
{
	if (Value <= MaxDifficultNumber && Value >= MinDifficultNumber) {
		DifficultNumber = Value;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Difficult level number out of bounds %d"), Value);
	}
}

void UGachiPatrolDifficultVisitor::VisitGachiPatrol(FGachiPosition& Position)
{
	// Deactivate gachi, if difficult is 0
	if (DifficultNumber == 0) {
		Position.Delay = 0;
	}
	// Determine new delay, that depends on DifficultNumber
	else {
		Position.Delay = Position.Delay * ((MaxDifficultNumber + 1 - DifficultNumber) * Coeficent);
	}
}
