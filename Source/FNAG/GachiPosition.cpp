// Fill out your copyright notice in the Description page of Project Settings.


#include "GachiPosition.h"

FGachiPosition::FGachiPosition()
{
	if (Delay <= 0.f) {
		Delay = 0.1f;
	}

}

FGachiPosition::~FGachiPosition()
{
}
