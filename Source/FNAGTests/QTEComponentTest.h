// Fill out your copyright notice in the Description page of Project Settings.
#if WITH_EDITOR
#pragma once

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"

#include "FNAG/QTEComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FQTEComponentBaseTest, "QTEComponent.Base", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter | EAutomationTestFlags::CriticalPriority);
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FQTEComponentLaunchTest, "QTEComponent.Launch", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter | EAutomationTestFlags::CriticalPriority);

#endif