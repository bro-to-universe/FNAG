// Fill out your copyright notice in the Description page of Project Settings.


#include "QTEComponentTest.h"

bool FQTEComponentBaseTest::RunTest(const FString& Parameters)
{
	UQTEComponent* const QTE = NewObject<UQTEComponent>();
	const FName XEvent = FName("X");
	const FName YEvent = FName("Y");

	QTE->AddEvent(XEvent);
	{
		TestEqual(TEXT("QTE has added event X"), QTE->GetEventByIndex(0), XEvent);
	}
	{
		QTE->AddEvent(YEvent);
		TestEqual(TEXT("QTE has added second event Y"), QTE->GetEventByIndex(1), YEvent);
	}
	{
		TestEqual(TEXT("QTE returns empty event when out of bounds"), QTE->GetEventByIndex(3), UQTEComponent::EmptyEvent);
	}

	const FName GeneratedEvent = QTE->GenerateRandomEvent();
	{
		TestNotEqual(TEXT("QTE generates event that is not equal to EmptyEvent"), GeneratedEvent, UQTEComponent::EmptyEvent);
	}

	const FName StoringEvent = QTE->GetStoringEvent();
	{
		TestEqual(TEXT("QTE generates event that is equal to storing"), StoringEvent, GeneratedEvent);
	}

	bool IsEventStoring = QTE->GetEventStoring();
	{
		TestEqual(TEXT("QTE should store event"), IsEventStoring, true);
	}

	QTE->ClearStoringEvent();
	IsEventStoring = QTE->GetEventStoring();
	{
		TestEqual(TEXT("QTE, after clearing, doesn't store event"), IsEventStoring, false);
	}

	return true;
}

bool FQTEComponentLaunchTest::RunTest(const FString& Parameters) {
	UQTEComponent* const QTE = NewObject<UQTEComponent>();
	FName XEvent = FName("X");
	QTE->AddEvent(XEvent);

	{
		QTE->LaunchEvent(5.f);
		TestEqual(TEXT("QTE stores X event"), QTE->GetStoringEvent(), XEvent);
	}
	{
		QTE->FinishEvent();
		TestEqual(TEXT("QTE after finishing should store empty event"), QTE->GetStoringEvent(), UQTEComponent::EmptyEvent);
	}

	{
		QTE->LaunchEvent(5.f);
		TestEqual(TEXT("QTE stores X event second time"), QTE->GetStoringEvent(), XEvent);
	}
	{
		QTE->ReactEvent();
		TestEqual(TEXT("QTE after reacting should store empty event"), QTE->GetStoringEvent(), UQTEComponent::EmptyEvent);
	}

	return true;
}