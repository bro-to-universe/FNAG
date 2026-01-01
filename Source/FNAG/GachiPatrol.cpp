// Fill out your copyright notice in the Description page of Project Settings.


#include "GachiPatrol.h"

// Sets default values for this component's properties
UGachiPatrol::UGachiPatrol()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UGachiPatrol::BeginPlay()
{
	Super::BeginPlay();

	// ...
	BranchesLength = Branches.Num();
	Branches[CurrentBranchIndex].Positions[0].Point->VisitPoint();
}


// Called every frame
void UGachiPatrol::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FGachiPosition UGachiPatrol::GetCurrentPosition()
{
	if (CurrentBranchIndex > -1 && CurrentBranchIndex < BranchesLength) {
		return Branches[CurrentBranchIndex].Positions[CurrentPositionIndex];
	}

	UE_LOG(LogTemp, Error, TEXT("Position's index out of bounds %d, point's length is %d"), CurrentBranchIndex, BranchesLength);
	return Branches[0].Positions[0];
}

FGachiBranch UGachiPatrol::GetCurrentBranch()
{
	if (CurrentBranchIndex > -1 && CurrentBranchIndex < BranchesLength) {
		return Branches[CurrentBranchIndex];
	}

	UE_LOG(LogTemp, Error, TEXT("Branch's index out of bounds %d, branches' length is %d"), CurrentBranchIndex, BranchesLength);
	return Branches[0];
}

bool UGachiPatrol::GetCurrentBranchAttacking()
{
	return GetCurrentBranch().bStartAttacking;
}

void UGachiPatrol::InitDifficultNumber(int Value)
{
	DifficultNumber = Value;

	UGachiPatrolDifficultVisitor* Visitor = NewObject<UGachiPatrolDifficultVisitor>(this);
	Visitor->SetDifficultNumber(DifficultNumber);
	Accept(Visitor);
}

void UGachiPatrol::NextPosition()
{
	ChangeCurrentIndex(1);
}

void UGachiPatrol::PrevPosition()
{
	ChangeCurrentIndex(-1);
}

void UGachiPatrol::SkipPosition()
{
	NextPosition();
	NextPosition();
}

bool UGachiPatrol::IsLastPosition()
{
	return BranchesLength == CurrentBranchIndex + 1;
}

void UGachiPatrol::ChangeCurrentIndex(int Value)
{
	// Calculate valid next branch index
	int NextBranchIndex = CurrentBranchIndex + Value;
	if (NextBranchIndex >= 0) {
		NextBranchIndex = NextBranchIndex % BranchesLength;
	}
	else {
		NextBranchIndex = 0;
	}

	// Calculate right next position index
	const TArray<FGachiPosition> NextBranchPositions = Branches[NextBranchIndex].Positions;
	const FGachiPosition Position = Branches[CurrentBranchIndex].Positions[CurrentPositionIndex];
	const int PositionsLength = NextBranchPositions.Num();
	int NextPositionIndex = FMath::RoundHalfToEven((float)(FMath::FRand() * (PositionsLength - 1)));
	for (int i = 0; i < PositionsLength; ++i) {
		if (Position.PathNumber == NextBranchPositions[i].PathNumber) {
			NextPositionIndex = i;
		}
	}

	// Visit new point, if it is empty
	AGachiPoint* NextPoint = NextBranchPositions[NextPositionIndex].Point;
	if (!NextPoint->IsPointBusy()) {
		Position.Point->LeftPoint();
		NextPoint->VisitPoint();
		CurrentBranchIndex = NextBranchIndex;
		CurrentPositionIndex = NextPositionIndex;
	}
}

void UGachiPatrol::Accept(UGachiPatrolVisitor* Visitor)
{
	for (auto& Branch : Branches) {
		for (auto& Position : Branch.Positions) {
			Visitor->VisitGachiPatrol(Position);
		}
	}
}
