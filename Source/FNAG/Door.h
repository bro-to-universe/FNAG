// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClickActor.h"
#include "Door.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDoorStateChangedSignature, bool, IsClosed);

UENUM(BlueprintType)
enum DoorType {
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right")
};

/**
 *
 */
UCLASS()
class FNAG_API ADoor : public AClickActor
{
	GENERATED_BODY()

public:

	ADoor();

	UFUNCTION(BlueprintCallable)
		void CloseDoor();
	UFUNCTION(BlueprintCallable)
		void OpenDoor();
	UFUNCTION(BlueprintCallable)
		void SetPlayerNextToDoor(bool Value);

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable);
	FOnDoorStateChangedSignature OnDoorStateChanged;

private:
	void SetClosedDoor(bool IsDoorClosed);

	void RotateDoor(float Amplifier);

public:

	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* Anchor;

	UPROPERTY(BlueprintReadOnly);
	bool IsClosed = false;

	UPROPERTY(BlueprintReadOnly);
	bool IsStartClosing = false;

	UPROPERTY(BlueprintReadOnly);
	bool IsPlayerNextToDoor = false;

	UPROPERTY(EditAnywhere);
	float MaxDeltaRotationAngle = 40.f;

	float ChangedAngle = 0.f;

	UPROPERTY(EditAnywhere);
	float SpeedRotation = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	TEnumAsByte<DoorType> Type;

};
