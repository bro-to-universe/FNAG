// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Misc/AutomationTest.h"
#include "CoreMinimal.h"

/**
 *
 */
class FTestModuleImpl : public FDefaultGameModuleImpl {

	void ShutdownModule() override;

	void UnregisterAutomationTest(FString TestName);
};
