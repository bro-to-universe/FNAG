// Fill out your copyright notice in the Description page of Project Settings.
#if WITH_EDITOR
#pragma once

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"

#include "FNAG/FlashLightComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFlashLightComponentTest, "FlashLightComponent", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter | EAutomationTestFlags::CriticalPriority)

#endif