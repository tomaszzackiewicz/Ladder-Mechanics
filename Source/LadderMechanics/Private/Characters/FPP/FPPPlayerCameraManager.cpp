// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/FPP/FPPPlayerCameraManager.h"

void AFPPPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	ViewPitchMin = PitchMin;
	ViewPitchMax = PitchMax;
}
