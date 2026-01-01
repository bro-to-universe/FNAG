// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EngineUtils.h"
#include "GachiBranch.h"
#include "GachiPatrolVisitor.h"
#include "GachiPatrolDifficultVisitor.h"
#include "GachiPatrol.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FNAG_API UGachiPatrol : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGachiPatrol();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	friend class UGachiPatrolVisitor;

	// Get current point
	UFUNCTION(BlueprintCallable)
		FGachiPosition GetCurrentPosition();

	// Get current branch
	UFUNCTION(BlueprintCallable)
		FGachiBranch GetCurrentBranch();

	// Get StartAttacking of branch
	UFUNCTION(BlueprintCallable)
		bool GetCurrentBranchAttacking();

	// Set difficult number and change delay of positions
	UFUNCTION(BlueprintCallable)
		void InitDifficultNumber(int Value);

	// Increment Current Index
	UFUNCTION(BlueprintCallable)
		void NextPosition();
	// Decrement Current Index
	UFUNCTION(BlueprintCallable)
		void PrevPosition();
	// Double NextPoint
	UFUNCTION(BlueprintCallable)
		void SkipPosition();

	UFUNCTION(BlueprintCallable)
		bool IsLastPosition();

public:
	// Add positions in view port
	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	TArray<FGachiBranch> Branches;

	// Difficult number for player: 0-20
	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	int DifficultNumber = 10;

	// Max difficult number
	int MaxDifficultNumber = 20;

private:
	// Change current index on Value
	void ChangeCurrentIndex(int Value);

	// Default path that take all gachi
	const int DefaultPath = 0;

	// Index of current element in branches
	int CurrentBranchIndex = 0;

	// Index of Positions in Current Branch
	int CurrentPositionIndex = 0;

	// Length of branches array 
	int BranchesLength = 0;

	// Accept changes from Visitor
	void Accept(UGachiPatrolVisitor* Visitor);

};
