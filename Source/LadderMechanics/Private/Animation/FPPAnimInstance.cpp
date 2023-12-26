// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/FPPAnimInstance.h"

#include "Characters/FPP/FPPCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UFPPAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* OwningPawn = TryGetPawnOwner();
	if (OwningPawn) {
		FPPCharacterBase = Cast<AFPPCharacterBase>(OwningPawn);
	}
}

void UFPPAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (!FPPCharacterBase) return;

	Velocity = FPPCharacterBase->GetVelocity();
	GroundSpeed = UKismetMathLibrary::VSizeXY(FPPCharacterBase->GetVelocity());
	bIsFalling = FPPCharacterBase->GetCharacterMovement()->IsFalling();
	
	const bool bIsNotEqual = UKismetMathLibrary::NotEqual_VectorVector(FPPCharacterBase->GetCharacterMovement()->GetCurrentAcceleration(),
		FVector(0) , 0.0f);

	bShouldMove = (bIsNotEqual && GroundSpeed > 3.0f) ? true : false;
}
