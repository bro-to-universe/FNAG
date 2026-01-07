// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickActor.h"

// Sets default values
AClickActor::AClickActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshForClick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshForClick"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	MeshToReturnPosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshToReturnPosition"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMeshComponent);
	MeshForClick->SetupAttachment(StaticMeshComponent);
}

// Called when the game starts or when spawned
void AClickActor::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate Subscriber;
	Subscriber.BindUFunction(this, "OnClickCallback");
	MeshForClick->OnClicked.Add(Subscriber);
}

// Called every frame
void AClickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AClickActor::OnClickCallback(UPrimitiveComponent* ClickedComponent, FKey ButtonClicked)
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked"));
	OnMyActorClicked.Broadcast(GetMeshReturnPosition());
}

FVector AClickActor::GetMeshReturnPosition()
{
	if (!MeshToReturnPosition) {
		UE_LOG(LogTemp, Error, TEXT("MeshToReturnPosition isn't initialized"));
	}
	return MeshToReturnPosition->GetComponentLocation();
}
