// Fill out your copyright notice in the Description page of Project Settings.


#include "GachiPoint.h"

// Sets default values
AGachiPoint::AGachiPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PositionMesh = CreateDefaultSubobject<UArrowComponent>(TEXT("PositionMesh"));
	RootComponent = PositionMesh;
}

// Called when the game starts or when spawned
void AGachiPoint::BeginPlay()
{
	Super::BeginPlay();

	PositionLocation = GetActorLocation();
	PositionRotation = GetActorRotation();
}

// Called every frame
void AGachiPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGachiPoint::GetLocationAndRotation(FVector& Location, FRotator& Rotation)
{
	Location = PositionLocation;
	Rotation = PositionRotation;
}

void AGachiPoint::VisitPoint()
{
	IsBusy = true;
}

void AGachiPoint::LeftPoint()
{
	IsBusy = false;
}

bool AGachiPoint::IsPointBusy()
{
	return IsBusy;
}

