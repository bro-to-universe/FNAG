// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainingBar.h"

ATrainingBar::ATrainingBar()
{
	PrimaryActorTick.bCanEverTick = false;

	LeftBarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftBar"));
	RightBarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightBar"));
	LeftBarMesh->SetupAttachment(StaticMeshComponent);
	RightBarMesh->SetupAttachment(StaticMeshComponent);
}

void ATrainingBar::PullUp()
{
	PullAnimation->GetSequencePlayer()->Play();
}

void ATrainingBar::PullDown() {
	PullAnimation->GetSequencePlayer()->PlayReverse();
}

void ATrainingBar::Training()
{
	TrainingAnimation->GetSequencePlayer()->Play();
}
