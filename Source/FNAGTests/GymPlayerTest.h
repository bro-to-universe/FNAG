// Fill out your copyright notice in the Description page of Project Settings.
#if WITH_EDITOR
#pragma once

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"

#include "FNAG/GymPlayer.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGymPlayerFlashLightSeatingTest, "GymPlayer.FlashLight.Seating", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::CriticalPriority | EAutomationTestFlags::ProductFilter);
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGymPlayerFlashLightStandingTest, "GymPlayer.FlashLight.Standing", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::CriticalPriority | EAutomationTestFlags::ProductFilter);
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGymPlayerFlashLightOtherActionTest, "GymPlayer.FlashLight.OtherAction", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::CriticalPriority | EAutomationTestFlags::ProductFilter);

#endif
