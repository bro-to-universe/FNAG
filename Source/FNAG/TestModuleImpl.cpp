// Fill out your copyright notice in the Description page of Project Settings.


#include "TestModuleImpl.h"

void FTestModuleImpl::ShutdownModule()
{
	UnregisterAutomationTest("FQTEComponentTest");
	UnregisterAutomationTest("FLevelConfigFactoryTest");
}

void FTestModuleImpl::UnregisterAutomationTest(FString TestName)
{
	FAutomationTestFramework::Get().UnregisterAutomationTest(TestName);
}
