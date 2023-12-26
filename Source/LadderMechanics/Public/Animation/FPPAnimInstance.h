// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPPAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LADDERMECHANICS_API UFPPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPPAnimInstance")
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPPAnimInstance")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPPAnimInstance")
	bool bIsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPPAnimInstance")
	bool bShouldMove;

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	UPROPERTY()
	class AFPPCharacterBase* FPPCharacterBase = nullptr;
	
};
