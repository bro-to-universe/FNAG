// Fill out your copyright notice in the Description page of Project Settings.


#include "GymPlayer.h"

// Sets default values
AGymPlayer::AGymPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
	FlashLightController = CreateDefaultSubobject<UFlashLightComponent>(TEXT("FlashLightController"));
	FlashLightController->Init(Flashlight);

}

// Called when the game starts or when spawned
void AGymPlayer::BeginPlay()
{
	Super::BeginPlay();

	PlayerController->SetShowMouseCursor(true);
	PlayerController->bEnableClickEvents = true;
	PlayerController->bBlockInput = false;

	FindDoors();
	BindDoorsEvents();
	FindTrainingBar();
	BindTrainingBarEvent();

	InitQTE();
	BindQTEFinishEvent();
	FindSecurityCameras();
	CheckDoubleSecurityCameras();

	InitPosition = GetActorLocation();
	InitRotation = GetActorRotation();

	OnActorsInitialized.Broadcast();
}

// Called every frame
void AGymPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Stamina += StaminaToChangedPerSecond * DeltaTime;
	if (Stamina > 100) {
		Stamina = 100.f;
	}
	else if (Stamina < 0) {
		Stamina = 0.f;
		GetLeftDoor()->OpenDoor();
		GetRightDoor()->OpenDoor();
	}

	if (ActionType == EPlayerActionType::Moving) {
		FVector PlayerPosition = GetActorLocation();
		FVector DeltaVector = DirectionVector * MovementSpeed * DeltaTime;

		if ((PositionToCome - PlayerPosition).Length() >= (PositionToCome - PlayerPosition - DeltaVector).Length()) {
			ChangeLocation(DeltaVector);
			OnPlayerMoving.Broadcast(PlayerPosition, false);
		}
		else {
			OnPlayerMoving.Broadcast(PositionToCome, true);
		}
	}
	else if (ActionType == EPlayerActionType::ForceRotating) {
		float DeltaLerp = DeltaTime * LurpRotationSpeed;
		float NextLerp = LurpRotationChanged + DeltaLerp;

		if (NextLerp < 1.f) {
			LurpRotationChanged = NextLerp;
			SetActorRotation(FMath::Lerp(GetActorRotation(), DirectionRotation, NextLerp));
		}
		else {
			LurpRotationChanged = 0.f;
			if (NextStandingActionType == EPlayerActionType::Standing && LastStandingActionType == EPlayerActionType::Standing) {
				SetActionType(EPlayerActionType::Standing);
			}
			else {
				SetActionType(EPlayerActionType::Moving);
			}
		}
	}

	OnStaminaChanged.Broadcast(Stamina);
}

// Called to bind functionality to input
void AGymPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGymPlayer::RotateLR(float Value) {
	auto Rotation = GetActorRotation();
	float DeltaYaw = RotationSpeed * Value;
	float NextChangedDeltaYaw = ChangedDeltaYaw + DeltaYaw;
	if (abs(NextChangedDeltaYaw) <= RotationDeltaYawLimit) {
		ChangedDeltaYaw = NextChangedDeltaYaw;
		Rotation.Yaw += DeltaYaw;
		SetActorRotation(Rotation);
		Flashlight->SetRelativeRotation(Rotation);
	}
}
void AGymPlayer::RotateUD(float Value)
{
	auto Rotation = GetActorRotation();
	float DeltaPitch = RotationSpeed * Value;
	float NextChangedDeltaPitch = ChangedDeltaPitch + DeltaPitch;
	if (abs(NextChangedDeltaPitch) <= RotationDeltaPitchLimit) {
		ChangedDeltaPitch = NextChangedDeltaPitch;
		Rotation.Pitch += DeltaPitch;
		SetActorRotation(Rotation);
		Flashlight->SetRelativeRotation(Rotation);
	}
}
void AGymPlayer::RotatePlayer(FRotator Rotation)
{
	ChangedDeltaPitch = 0;
	ChangedDeltaYaw = 0;
	DirectionRotation = Rotation;
	SetActionType(EPlayerActionType::ForceRotating);
}
void AGymPlayer::RotatePlayerToInitRotation() {
	RotatePlayer(InitRotation);
}

void AGymPlayer::ComeToPosition(FVector Position) {
	if (ActionType != EPlayerActionType::Moving && ActionType != EPlayerActionType::ForceRotating) {
		if (ActionType == EPlayerActionType::Seating) {
			StandUp();
		}
		DirectionVector = (Position - GetActorLocation());
		DirectionVector.Normalize();
		PositionToCome = Position;
		RotatePlayer(DirectionVector.Rotation());
	}
}
void AGymPlayer::ComeBackToInitPosition()
{
	switch (ActionType) {
	case EPlayerActionType::TrainingBarStanding:
		GetTrainingBar()->PullDown();
	case EPlayerActionType::RightDoorStanding:
	case EPlayerActionType::LeftDoorStanding:
		SetNextStandingActionType(EPlayerActionType::Standing);
	}

	ComeToPosition(InitPosition);
}
void AGymPlayer::HandleComeback()
{
	switch (ActionType) {
	case EPlayerActionType::LeftDoorClosing:
	case EPlayerActionType::RightDoorClosing:
		break;
	case EPlayerActionType::LeftDoorStanding:
	case EPlayerActionType::RightDoorStanding:
		GetLeftDoor()->SetPlayerNextToDoor(false);
		GetRightDoor()->SetPlayerNextToDoor(false);
	case EPlayerActionType::TrainingBarStanding:
		ClearQTETimer();
	default:
		ComeBackToInitPosition();
	}
}

void AGymPlayer::StandUp()
{
	if (ActionType == EPlayerActionType::Seating) {
		SetActionType(EPlayerActionType::Standing);
		ChangeLocation(FVector(0.f, 0.f, 20.f));
	}
}
void AGymPlayer::SeatDown()
{
	if (ActionType == EPlayerActionType::Standing) {
		SetActionType(EPlayerActionType::Seating);
		ChangeLocation(FVector(0.f, 0.f, -20.f));
	}
}
void AGymPlayer::ChangeLocation(FVector DeltaVector)
{
	auto Location = GetActorLocation();
	Location += DeltaVector;
	SetActorLocation(Location);
}

void AGymPlayer::SetActionType(TEnumAsByte<EPlayerActionType> Value)
{
	if (!(IsActionTypeEqualTo(EPlayerActionType::Moving) || IsActionTypeEqualTo(EPlayerActionType::ForceRotating))) {
		LastStandingActionType = ActionType;
	}
	FlashLightController->TurnOff();
	ActionType = Value;

	switch (Value) {
	case EPlayerActionType::LeftDoorClosing:
	case EPlayerActionType::RightDoorClosing:
		SetStaminaToChangedPerSecond(-5.f);
		break;

	case EPlayerActionType::Seating:
		SetStaminaToChangedPerSecond(1.f);
		break;

	case EPlayerActionType::Moving:
		SetStaminaToChangedPerSecond(-1.f);
		break;

	case EPlayerActionType::Standing:
	case EPlayerActionType::LeftDoorStanding:
	case EPlayerActionType::RightDoorStanding:
		SetStaminaToChangedPerSecond(0.f);
		break;

	case EPlayerActionType::SeatingFlashLight:
		FlashLightController->TurnOn();
		break;
	case EPlayerActionType::StandingFlashLight:
		FlashLightController->TurnOn();
		break;

	default:
		SetStaminaToChangedPerSecond(0.f);
	}

	OnActionTypeChanged.Broadcast(ActionType);
}
void AGymPlayer::SetNextStandingActionType(TEnumAsByte<EPlayerActionType> Value)
{
	NextStandingActionType = Value;
}
void AGymPlayer::HandleNextActionType()
{
	SetActionType(NextStandingActionType);
	switch (NextStandingActionType) {
	case EPlayerActionType::LeftDoorStanding:
		GetLeftDoor()->SetPlayerNextToDoor(true);
		break;
	case EPlayerActionType::RightDoorStanding:
		GetRightDoor()->SetPlayerNextToDoor(true);
		break;
	case EPlayerActionType::Standing:
		RotatePlayerToInitRotation();
		break;
	case EPlayerActionType::TrainingBarStanding:
		TrainingBar->PullUp();
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Next action type %d not handled"), NextStandingActionType);
	}
}
bool AGymPlayer::IsActionTypeEqualTo(TEnumAsByte<EPlayerActionType> Value)
{
	return ActionType == Value;
}

void AGymPlayer::SetStamina(float NewStamina)
{
	Stamina = NewStamina;
}
void AGymPlayer::SetStaminaToChangedPerSecond(float Value)
{
	StaminaToChangedPerSecond = Value * AmplifierStaminaToChangedPerSecond;
}
void AGymPlayer::BoostStaminaToChangedPerSecond() {
	AmplifierStaminaToChangedPerSecond *= AmplifierAmplifierStaminaToChangedPerSecond;
}

ADoor* AGymPlayer::GetDoor(TEnumAsByte<DoorType> Type)
{
	switch (Type) {
	case DoorType::Left:
		if (!LeftDoor) {
			UE_LOG(LogTemp, Error, TEXT("Tried get left door before initializing"));
		}
		return LeftDoor;
	case DoorType::Right:
		if (!RightDoor) {
			UE_LOG(LogTemp, Error, TEXT("Tried get right door before initializing"));
		}
		return RightDoor;
	}

	return nullptr;
}
void AGymPlayer::BoostQTEDelay()
{
	AmplifierQTEDelay *= AmplifierAmplifierQTEDelay;
}
void AGymPlayer::LaunchQTE()
{
	UWorld* World = GetWorld();
	if (World) {
		ClearQTETimer();
		World->GetTimerManager().SetTimer(QTENextTimer, this, &AGymPlayer::HandleLaunchQTE, GetTrainingBar()->MsBetweenAnimations, false);
	}
}
void AGymPlayer::HandleLaunchQTE()
{
	QTE->LaunchEvent(QTEDelay * AmplifierQTEDelay);
	OnQTEGeneratedEvent.Broadcast(QTE->GetStoringEvent(), QTEDelay * AmplifierQTEDelay);
}
void AGymPlayer::ClearQTETimer()
{
	UWorld* World = GetWorld();
	if (World) {
		World->GetTimerManager().ClearTimer(QTENextTimer);
		QTE->ClearStoringEvent();
	}
}
void AGymPlayer::InitQTE()
{
	QTE = NewObject<UQTEComponent>();
	QTE->AddEvent(FName("X"));
	QTE->AddEvent(FName("Y"));
	QTE->AddEvent(FName("B"));
}
void AGymPlayer::QTEFinishEvent(bool IsSuccess) {
	if (IsSuccess) {
		BoostQTEDelay();
		BoostStaminaToChangedPerSecond();
		GetTrainingBar()->Training();
		UE_LOG(LogTemp, Warning, TEXT("Boosted Stamina and delay"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to react qte"));
	}
	LaunchQTE();
}
void AGymPlayer::BindQTEFinishEvent() {
	FScriptDelegate Subscriber;
	Subscriber.BindUFunction(this, FName("QTEFinishEvent"));
	QTE->OnQTEFinished.Add(Subscriber);
}
ADoor* AGymPlayer::GetLeftDoor() {
	return GetDoor(DoorType::Left);
}
ADoor* AGymPlayer::GetRightDoor() {
	return GetDoor(DoorType::Right);
}
void AGymPlayer::ReactQTE(FName EventName)
{
	if (QTE->StoringEvent == EventName && EventName != UQTEComponent::EmptyEvent) {
		QTE->ReactEvent();
	}
	else {
		QTE->FinishEvent();
	}
}
void AGymPlayer::TurnFlashLightOn()
{
	if (ActionType == EPlayerActionType::Standing) {
		SetActionType(EPlayerActionType::StandingFlashLight);
	}
	else if (ActionType == EPlayerActionType::Seating) {
		SetActionType(EPlayerActionType::SeatingFlashLight);
	}
}
void AGymPlayer::TurnFlashLightOff()
{
	if (ActionType == EPlayerActionType::StandingFlashLight) {
		SetActionType(EPlayerActionType::Standing);
	}
	else if (ActionType == EPlayerActionType::SeatingFlashLight) {
		SetActionType(EPlayerActionType::Seating);
	}
}
void AGymPlayer::FindDoors()
{
	UWorld* World = GetWorld();
	for (TActorIterator<ADoor> It(World); It; ++It) {
		switch (It->Type)
		{
		case DoorType::Left:
			if (LeftDoor == NULL) {
				LeftDoor = *It;
			}
			else {
				UE_LOG(LogTemp, Error, TEXT("The left door should be only one"));
			}
			break;
		case DoorType::Right:
			if (RightDoor == NULL) {
				RightDoor = *It;
			}
			else {
				UE_LOG(LogTemp, Error, TEXT("The right door should be only one"));
			}
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("The door anomaly"));
			break;
		}
	}
	if (LeftDoor == NULL) {
		UE_LOG(LogTemp, Error, TEXT("The left door not in scene"));
	} if (RightDoor == NULL) {
		UE_LOG(LogTemp, Error, TEXT("The right door not in scene"));
	}
}

void AGymPlayer::SwitchSecurityCameraView(FString CameraId)
{
	if (IsActionTypeEqualTo(EPlayerActionType::Seating) || IsActionTypeEqualTo(EPlayerActionType::CheckingSecurityCameras)) {
		bool blended = false;
		for (int i = 0; i < SecurityCameras.Num(); ++i) {
			if (SecurityCameras[i]->CameraId == CameraId) {
				PlayerController->SetViewTargetWithBlend(SecurityCameras[i], 0.f);
				LastOpenedSecurityCameraId = CameraId;
				blended = true;
				OnSecurityCameraSwitched.Broadcast(SecurityCameras[i]->IsBroken);
			}
		}
		if (!blended) {
			UE_LOG(LogTemp, Error, TEXT("This CameraId doesn't exist"));
		}
	}
}
void AGymPlayer::SetPlayerCameraView()
{
	PlayerController->SetViewTargetWithBlend(this, 0.f);
}
void AGymPlayer::CheckDoubleSecurityCameras() {
	for (int i = 0; i < SecurityCameras.Num(); ++i) {
		int count = 0;
		for (int j = 0; j < SecurityCameras.Num(); ++j) {
			if (SecurityCameras[i]->CameraId == SecurityCameras[j]->CameraId)
			{
				count++;
			}
		}
		if (count > 1) {
			UE_LOG(LogTemp, Fatal, TEXT("More than one security camera have the same CameraId"));
		}
	}
}
void AGymPlayer::FindSecurityCameras()
{
	UWorld* World = GetWorld();
	for (TActorIterator<ASecurityCamera> It(World); It; ++It) {
		SecurityCameras.Add(*It);
	}
}

void AGymPlayer::BindDoorsEvents()
{
	FScriptDelegate LeftDoorStateChangedSubscriber;
	LeftDoorStateChangedSubscriber.BindUFunction(this, FName("LeftDoorStateChangedEvent"));
	FScriptDelegate ClickLeftDoorSubscriber;
	ClickLeftDoorSubscriber.BindUFunction(this, FName("ClickLeftDoorEvent"));
	if (GetLeftDoor()) {
		LeftDoor->OnDoorStateChanged.Add(LeftDoorStateChangedSubscriber);
		LeftDoor->OnMyActorClicked.Add(ClickLeftDoorSubscriber);
	}

	FScriptDelegate RightDoorStateChangedSubscriber;
	RightDoorStateChangedSubscriber.BindUFunction(this, FName("RightDoorStateChangedEvent"));
	FScriptDelegate ClickRightDoorSubscriber;
	ClickRightDoorSubscriber.BindUFunction(this, FName("ClickRightDoorEvent"));
	if (GetRightDoor()) {
		RightDoor->OnDoorStateChanged.Add(RightDoorStateChangedSubscriber);
		RightDoor->OnMyActorClicked.Add(ClickRightDoorSubscriber);
	}
}
void AGymPlayer::ClickLeftDoorEvent(FVector DoorLocation)
{
	ClickDoorEvent(EPlayerActionType::LeftDoorStanding, DoorLocation);
}
void AGymPlayer::ClickRightDoorEvent(FVector DoorLocation)
{
	ClickDoorEvent(EPlayerActionType::RightDoorStanding, DoorLocation);
}
void AGymPlayer::ClickDoorEvent(TEnumAsByte<EPlayerActionType> NextDoorStandingType, FVector DoorLocation)
{
	if (!IsActionTypeEqualTo(NextDoorStandingType)) {
		UE_LOG(LogTemp, Warning, TEXT("Click door triggered"));
		ComeToPosition(DoorLocation);

		SetNextStandingActionType(NextDoorStandingType);
	}
}
void AGymPlayer::LeftDoorStateChangedEvent(bool IsClosed)
{
	DoorStateChangedEvent(EPlayerActionType::LeftDoorClosing, EPlayerActionType::LeftDoorStanding, IsClosed);
}
void AGymPlayer::RightDoorStateChangedEvent(bool IsClosed)
{
	DoorStateChangedEvent(EPlayerActionType::RightDoorClosing, EPlayerActionType::RightDoorStanding, IsClosed);
}
void AGymPlayer::DoorStateChangedEvent(TEnumAsByte<EPlayerActionType> DoorClosingType, TEnumAsByte<EPlayerActionType> DoorStandingType, bool IsClosed)
{
	if (IsClosed) {
		SetActionType(DoorClosingType);
	}
	else {
		SetActionType(DoorStandingType);
	}
}

void AGymPlayer::FindTrainingBar()
{
	for (TActorIterator<ATrainingBar> It(GetWorld()); It; ++It) {
		if (!TrainingBar) {
			TrainingBar = *It;
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("In game should be only one TrainingBar"));
		}
	}
}

void AGymPlayer::BindTrainingBarEvent()
{
	FScriptDelegate Subscriber;
	Subscriber.BindUFunction(this, FName("ClickTrainingBarEvent"));
	GetTrainingBar()->OnMyActorClicked.Add(Subscriber);
}

void AGymPlayer::ClickTrainingBarEvent(FVector TrainingBarLocation)
{
	if (!IsActionTypeEqualTo(EPlayerActionType::TrainingBarStanding)) {
		ComeToPosition(TrainingBarLocation);
		SetNextStandingActionType(EPlayerActionType::TrainingBarStanding);
		LaunchQTE();
	}
}

ATrainingBar* AGymPlayer::GetTrainingBar()
{
	if (!TrainingBar) {
		UE_LOG(LogTemp, Error, TEXT("Tried get TrainingBar before initialized"));
	}
	return TrainingBar;
}
