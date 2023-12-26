// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "FPPPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class LADDERMECHANICS_API AFPPPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pitch Values", meta = (AllowPrivateAccess = "true"))
	float PitchMin = -80.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pitch Values", meta = (AllowPrivateAccess = "true"))
	float PitchMax = 80.0f;
	
};
