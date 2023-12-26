// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "FPPCharacterBase.generated.h"

class UInputComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class ALadder;

UCLASS()
class LADDERMECHANICS_API AFPPCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPPCharacterBase();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	void SetMaxWalkSpeed(float MaxWalkSpeed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Interact();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPPCharacterBase")
	float FacingDistanceToObject = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPPCharacterBase")
	float MinFacingToObject = -0.95f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPPCharacterBase")
	float MaxFacingToObject = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPPCharacterBase")
	float WalkSpeed = 230.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPPCharacterBase")
	float RunSpeed = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	bool IsOnLadder = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	bool IsNearLadder = false;

	UPROPERTY()
	ALadder* Ladder = nullptr;

	TArray<AActor*> FoundActors;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* TorsoSkeletalMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* LegsSkeletalMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FeetSkeletalMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FaceSkeletalMeshComponent = nullptr;

	bool IsOnLadderToggled = false;

	bool IsFacingToLadder = false;

	UFUNCTION()
	void GetSideClosebyRayHits();

	FTimerHandle CheckgroundTimerHandle;

	float CharacterZAxis = 0.0f;

	bool IsCharacterUpLadder = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetLadder(ALadder* LadderParam);
	void SetIsNearLadder(bool IsNearLadderParam);
	void SetIsOnLadder(bool IsOnLadderParam);
	void SetCharacterMovementMode(EMovementMode MovementModeParam);
	void SetCharacterGravityScale(float GravityScaleParam);
	void SetBrakingDecelerationFlying(float BrakingDecelerationFlyingParam);

	FORCEINLINE bool GetIsOnLadder() const { return IsOnLadder; }
	FORCEINLINE bool GetIsNearLadder() const { return IsNearLadder; }
};
