// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ClickActor.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMyActorClickedSignature, FVector, ActorPosition);

UCLASS()
class FNAG_API AClickActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AClickActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void OnClickCallback(UPrimitiveComponent* ClickedComponent, FKey ButtonClicked);

public:
	// Event dispatcher, broadcast when someone clicked and return actor's location
	UPROPERTY(BlueprintAssignable);
	FOnMyActorClickedSignature OnMyActorClicked;

	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* MeshForClick;

	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* MeshToReturnPosition;

	UPROPERTY(EditAnywhere);
	UBoxComponent* BoxCollision;

};
