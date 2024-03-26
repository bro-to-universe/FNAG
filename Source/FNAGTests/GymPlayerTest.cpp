


#include "GymPlayerTest.h"

bool FGymPlayerFlashLightSeatingTest::RunTest(const FString& Parameters) {
	UWorld* const World = FAutomationEditorCommonUtils::CreateNewMap();
	AGymPlayer* const GymPlayer = World->SpawnActor<AGymPlayer>();

	GymPlayer->SetActionType(EPlayerActionType::Seating);

	{
		TestEqual(TEXT("Flashlight should be turned off on Initialization"), GymPlayer->Flashlight->Intensity, GymPlayer->FlashLightController->IntensityValueOff);
	}
	{
		GymPlayer->TurnFlashLightOn();
		TestEqual(TEXT("Flashlight should be turned on after call TurnFlashLightOn"), GymPlayer->Flashlight->Intensity, GymPlayer->FlashLightController->IntensityValueOn);
	}
	{
		GymPlayer->TurnFlashLightOff();
		TestEqual(TEXT("Flashlight should be turned off after call TurnFlashLightOff"), GymPlayer->Flashlight->Intensity, GymPlayer->FlashLightController->IntensityValueOff);
	}

	return true;
}

bool FGymPlayerFlashLightStandingTest::RunTest(const FString& Parameters) {
	UWorld* const World = FAutomationEditorCommonUtils::CreateNewMap();
	AGymPlayer* const GymPlayer = World->SpawnActor<AGymPlayer>();

	GymPlayer->SetActionType(EPlayerActionType::Standing);

	{
		TestEqual(TEXT("Flashlight should be turned off on Initialization"), GymPlayer->Flashlight->Intensity, GymPlayer->FlashLightController->IntensityValueOff);
	}
	{
		GymPlayer->TurnFlashLightOn();
		TestEqual(TEXT("Flashlight should be turned on after call TurnFlashLightOn"), GymPlayer->Flashlight->Intensity, GymPlayer->FlashLightController->IntensityValueOn);
	}
	{
		GymPlayer->TurnFlashLightOff();
		TestEqual(TEXT("Flashlight should be turned off after call TurnFlashLightOff"), GymPlayer->Flashlight->Intensity, GymPlayer->FlashLightController->IntensityValueOff);
	}

	return true;
}

bool FGymPlayerFlashLightOtherActionTest::RunTest(const FString& Parameters) {
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	AGymPlayer* GymPlayer = World->SpawnActor<AGymPlayer>();

	GymPlayer->SetActionType(EPlayerActionType::LeftDoorStanding);

	{
		TestEqual(TEXT("Flashlight should be turned off on Initialization"), GymPlayer->Flashlight->Intensity, GymPlayer->FlashLightController->IntensityValueOff);
	}
	{
		GymPlayer->TurnFlashLightOn();
		TestEqual(TEXT("Flashlight should be turned on after call TurnFlashLightOn"), GymPlayer->Flashlight->Intensity, GymPlayer->FlashLightController->IntensityValueOff);
	}
	{
		GymPlayer->TurnFlashLightOff();
		TestEqual(TEXT("Flashlight should be turned off after call TurnFlashLightOff"), GymPlayer->Flashlight->Intensity, GymPlayer->FlashLightController->IntensityValueOff);
	}

	return true;
}