// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "GameManager.h"
#include "Door.h"
#include "TrainingBar.h"
#include "PlayerActionType.h"
#include "SecurityCamera.h"
#include "QTEComponent.h"
#include "FlashLightComponent.h"
#include "GymPlayer.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSecurityCameraSwitchedSignature, bool, IsBroken);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChangedSignature, float, Stamina);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorsInitializedSignature);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionTypeChangedSignature, EPlayerActionType, ActionType);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerMovingSignature, FVector, PlayerPosition, bool, IsMovingFinished);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQTEGeneratedEventSignature, FName, EventName, float, Delay);

UCLASS()
class FNAG_API AGymPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGymPlayer();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Rotate player in left, right: depends on Value
	UFUNCTION(BlueprintCallable)
		void RotateLR(float Value);
	// Rotate player in up and down: depends on Value
	UFUNCTION(BlueprintCallable)
		void RotateUD(float Value);
	// Force rotate player to initialized rotation 
	UFUNCTION(BlueprintCallable)
		void RotatePlayerToInitRotation();
	// Force rotate player to desired rotation
	UFUNCTION(BlueprintCallable)
		void RotatePlayer(FRotator Rotation);

	// Make player go to end position
	UFUNCTION(BlueprintCallable)
		void ComeToPosition(FVector Position);
	// Return player to initialized position
	UFUNCTION(BlueprintCallable)
		void ComeBackToInitPosition();
	// Make comeback right
	UFUNCTION(BlueprintCallable)
		void HandleComeback();

	// Move player to up
	UFUNCTION(BlueprintCallable)
		void StandUp();
	// Move player to down
	UFUNCTION(BlueprintCallable)
		void SeatDown();
	// Shift position on delta vector
	UFUNCTION(BlueprintCallable)
		void ChangeLocation(FVector DeltaVector);

	// Set security camera's view, return true if camera is broken or doesn't exist
	UFUNCTION(BlueprintCallable)
		void SwitchSecurityCameraView(FString CameraId);
	// Set player's view
	UFUNCTION(BlueprintCallable)
		void SetPlayerCameraView();

	// Set action type to Value
	UFUNCTION(BlueprintCallable)
		void SetActionType(TEnumAsByte<EPlayerActionType> Value);
	// Set next action type to Value
	UFUNCTION(BlueprintCallable)
		void SetNextStandingActionType(TEnumAsByte<EPlayerActionType> Value);
	// Define next behavior of player 
	UFUNCTION(BlueprintCallable)
		void HandleNextActionType();
	// Return true, if action type equal to Value
	UFUNCTION(BlueprintCallable)
		bool IsActionTypeEqualTo(TEnumAsByte<EPlayerActionType> Value);

	// Get left door in game
	UFUNCTION(BlueprintCallable)
		ADoor* GetLeftDoor();
	// Get right door in game
	UFUNCTION(BlueprintCallable)
		ADoor* GetRightDoor();

	UFUNCTION(BlueprintCallable)
		void ReactQTE(FName EventName);

	UFUNCTION(BlueprintCallable)
		void TurnFlashLightOn();
	UFUNCTION(BlueprintCallable)
		void TurnFlashLightOff();

	// Event for tracking player's position
	UPROPERTY(BlueprintAssignable);
	FOnPlayerMovingSignature OnPlayerMoving;
	// Event for notify when new camera turned on
	UPROPERTY(BlueprintAssignable);
	FOnSecurityCameraSwitchedSignature OnSecurityCameraSwitched;
	// Event for notify when all actors found (Doors, Security Cameras)
	UPROPERTY(BlueprintAssignable);
	FOnActorsInitializedSignature OnActorsInitialized;
	// Notify when stamina changed
	UPROPERTY(BlueprintAssignable);
	FOnStaminaChangedSignature OnStaminaChanged;
	// Notify when action type changed
	UPROPERTY(BlueprintAssignable);
	FOnActionTypeChangedSignature OnActionTypeChanged;
	// Notify when new QTE event appears
	UPROPERTY(BlueprintAssignable);
	FOnQTEGeneratedEventSignature OnQTEGeneratedEvent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	// Player's vision 
	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	UCameraComponent* PlayerCamera;
	// Security cameras in level
	UPROPERTY(BlueprintReadOnly);
	TArray<ASecurityCamera*> SecurityCameras;
	// The last opened security camera id in tablet
	UPROPERTY(BlueprintReadOnly, EditAnywhere, NoClear);
	FString LastOpenedSecurityCameraId;

	// Flashlight in game
	UPROPERTY(EditAnywhere);
	UFlashLightComponent* FlashLightController;
	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	USpotLightComponent* Flashlight;
	// Left door in game
	UPROPERTY(BlueprintReadOnly);
	ADoor* LeftDoor;
	// Right door in game
	UPROPERTY(BlueprintReadOnly);
	ADoor* RightDoor;
	// Training bar in game
	UPROPERTY(BlueprintReadOnly);
	ATrainingBar* TrainingBar;
	// Handling TrainingBar's qte
	UPROPERTY(BlueprintReadOnly);
	UQTEComponent* QTE;

	// Player's initialized position
	UPROPERTY(BlueprintReadOnly);
	FVector InitPosition;
	// Player's initialized rotation
	UPROPERTY(BlueprintReadOnly);
	FRotator InitRotation;

	// Behavior of player in game  
	UPROPERTY(BlueprintReadOnly);
	TEnumAsByte<EPlayerActionType> ActionType = EPlayerActionType::Seating;
	// Next behavior game
	UPROPERTY(BlueprintReadOnly);
	TEnumAsByte<EPlayerActionType> NextStandingActionType = EPlayerActionType::Standing;
	// Last behavior in game
	UPROPERTY(BlueprintReadOnly);
	TEnumAsByte<EPlayerActionType> LastStandingActionType = EPlayerActionType::Seating;


protected:
	// Speed of movement when go somewhere
	UPROPERTY(EditAnywhere);
	float MovementSpeed = 1.f;

	// Speed of force rotating
	UPROPERTY(EditAnywhere);
	float LurpRotationSpeed = 1.f;

	// Speed of controllable rotation by player
	UPROPERTY(EditAnywhere);
	float RotationSpeed = 1.f;

	// Yaw's delta limit 
	UPROPERTY(EditAnywhere);
	float RotationDeltaYawLimit = 45.f;
	// Pitch's delta Limit
	UPROPERTY(EditAnywhere);
	float RotationDeltaPitchLimit = 30.f;

private:
	// Yaw that turn player
	float ChangedDeltaYaw = 0.f;
	// Pitch that turn player
	float ChangedDeltaPitch = 0.f;

	// Direction where player will go
	FVector DirectionVector;
	// Next rotation
	FRotator DirectionRotation;
	// Coordinates of position where player go
	FVector PositionToCome;
	// Counter for percentage of rotation (0 -> 1)
	float LurpRotationChanged = 0.f;

	// Stamina of security boy, that show how much he can do
	float Stamina = 100.f;
	// Stamina multiplier for change security boy's stamina
	float StaminaToChangedPerSecond = 0.f;

	// For change view of camera in game
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	// Set Stamina to Value
	void SetStamina(float Value);
	// Set Stamina To Changed Per Second to Value
	void SetStaminaToChangedPerSecond(float Value);
	void BoostStaminaToChangedPerSecond();
	// Amplifier for StaminaPerSecond
	float AmplifierStaminaToChangedPerSecond = 1.f;
	// Amplifier for amplifier for StaminaPerSecond
	const float AmplifierAmplifierStaminaToChangedPerSecond = 0.9f;

	// Find all exist doors in game
	void FindDoors();
	// Find training bar in game
	void FindTrainingBar();

	// Bind doors' clicks and state events
	void BindDoorsEvents();
	// Template of click event for door
	void ClickDoorEvent(TEnumAsByte<EPlayerActionType> NextDoorStandingType, FVector DoorLocation);
	UFUNCTION()
		void ClickLeftDoorEvent(FVector DoorLocation);
	UFUNCTION()
		void ClickRightDoorEvent(FVector DoorLocation);
	// Template of state changed event for door
	void DoorStateChangedEvent(TEnumAsByte<EPlayerActionType> DoorClosingType, TEnumAsByte<EPlayerActionType> DoorStandingType, bool IsClosed);
	UFUNCTION()
		void LeftDoorStateChangedEvent(bool IsClosed);
	UFUNCTION()
		void RightDoorStateChangedEvent(bool IsClosed);

	// Bind TrainingBar's click event
	void BindTrainingBarEvent();
	// Handle TrainingBar's click event
	UFUNCTION()
		void ClickTrainingBarEvent(FVector TrainingBarLocation);

	// Launch QTE 
	void LaunchQTE();
	// Clear timer for qte
	void ClearQTETimer();
	// Handle launch qte
	void InitQTE();
	UFUNCTION()
		void HandleLaunchQTE();
	// Bind finishing qte
	void BindQTEFinishEvent();
	// Handle qte's finish
	UFUNCTION()
		void QTEFinishEvent(bool IsSuccess);
	// Amplifier for change qte's delay
	void BoostQTEDelay();
	float QTEDelay = 5.f;
	float AmplifierQTEDelay = 1.f;
	// How will change amplifier
	const float AmplifierAmplifierQTEDelay = 0.9f;

	FTimerHandle QTENextTimer;

	// Get door by type of door
	ADoor* GetDoor(TEnumAsByte<DoorType> Type);

	// Get training bar
	ATrainingBar* GetTrainingBar();

	// Check on repeated security cameras id in level, if find, will crush
	void CheckDoubleSecurityCameras();

	// Find all exist security cameras in game
	void FindSecurityCameras();
};
