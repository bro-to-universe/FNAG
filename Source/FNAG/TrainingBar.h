// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClickActor.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "TrainingBar.generated.h"

/**
 *
 */
UCLASS()
class FNAG_API ATrainingBar : public AClickActor
{
	GENERATED_BODY()

public:
	ATrainingBar();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ALevelSequenceActor* PullAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ALevelSequenceActor* TrainingAnimation;
	UFUNCTION(BlueprintCallable)
		void PullUp();
	UFUNCTION(BlueprintCallable)
		void PullDown();
	UFUNCTION(BlueprintCallable)
		void Training();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* LeftBarMesh;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* RightBarMesh;
	UPROPERTY(EditAnywhere)
		float MsBetweenAnimations = 5.f;

};
