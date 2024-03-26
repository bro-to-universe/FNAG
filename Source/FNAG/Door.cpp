// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

ADoor::ADoor() {
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);

	Anchor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Anchor"));
	RootComponent = Anchor;
	StaticMeshComponent->SetupAttachment(Anchor);
	MeshForClick->SetupAttachment(Anchor);
	MeshToReturnPosition->SetupAttachment(Anchor);
}

void ADoor::CloseDoor()
{
	IsStartClosing = true;
}

void ADoor::OpenDoor()
{
	IsStartClosing = false;
}

void ADoor::SetPlayerNextToDoor(bool Value)
{
	if (ChangedAngle == 0 || Value) {
		SetActorTickEnabled(Value);
	}
	IsStartClosing = false;
	IsPlayerNextToDoor = Value;
}

void ADoor::Tick(float DeltaTime)
{
	if (IsStartClosing) {
		if (abs(ChangedAngle) < abs(MaxDeltaRotationAngle)) {
			RotateDoor(DeltaTime);
		}
		else if (!IsClosed) {
			SetClosedDoor(true);
		}
	}
	else {
		//Check on difference signs
		if (!(ChangedAngle > 0 && MaxDeltaRotationAngle < 0) && !(ChangedAngle < 0 && MaxDeltaRotationAngle>0)) {
			RotateDoor(-1 * DeltaTime);
		}
		else if (IsClosed) {
			ChangedAngle = 0.f;
			SetClosedDoor(false);
			if (!IsPlayerNextToDoor) {
				SetActorTickEnabled(false);
			}
		}
	}

}

void ADoor::SetClosedDoor(bool IsDoorClosed)
{
	IsClosed = IsDoorClosed;
	OnDoorStateChanged.Broadcast(IsDoorClosed);
}

void ADoor::RotateDoor(float Amplifier)
{
	auto Rotation = GetActorRotation();
	float RotationAngle = SpeedRotation * Amplifier;
	ChangedAngle += RotationAngle;
	Rotation.Yaw += RotationAngle;
	SetActorRotation(Rotation);
}
