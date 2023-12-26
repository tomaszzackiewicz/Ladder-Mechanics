// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/FPP/FPPCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Objects/Ladder.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFPPCharacterBase::AFPPCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh(), FName("head"));
	CameraBoom->TargetArmLength = 1.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(CameraBoom);
	//FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	//FirstPersonCameraComponent->bUsePawnControlRotation = true;

	TorsoSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TorsoSkeletalMeshComponent"));
	TorsoSkeletalMeshComponent->SetupAttachment(GetMesh());

	LegsSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LegsSkeletalMeshComponent"));
	LegsSkeletalMeshComponent->SetupAttachment(GetMesh());

	FeetSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FeetSkeletalMeshComponent"));
	FeetSkeletalMeshComponent->SetupAttachment(GetMesh());

	FaceSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FaceSkeletalMeshComponent"));
	FaceSkeletalMeshComponent->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void AFPPCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALadder::StaticClass(), FoundActors);
	
	SetMaxWalkSpeed(WalkSpeed);
}

// Called every frame
void AFPPCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MovementMode: %s"), *UEnum::GetValueAsString(this->GetCharacterMovement()->MovementMode)));
	
	if (Ladder) {

		float DotProduct = FVector::DotProduct(this->GetActorForwardVector().GetSafeNormal(), Ladder->GetActorForwardVector().GetSafeNormal());
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: %f"), ));
		IsFacingToLadder = (DotProduct < MaxFacingToObject && DotProduct > MinFacingToObject)? true : false;

		if (IsOnLadder) {

			FRotator CharacterRot = this->GetActorRotation();
			FRotator LadderRot = Ladder->GetActorRotation();
			FRotator NewCharacterRot(CharacterRot.Pitch, CharacterRot.Roll, LadderRot.Yaw - 90);
			this->SetActorRotation(NewCharacterRot);

			//if (IsCharacterUpLadder)
			//{
			//	if (this->GetActorLocation().Z <= CharacterZAxis - 25.0f) {
			//		//SetCharacterMovementMode(EMovementMode::MOVE_Flying);
			//		//SetBrakingDecelerationFlying(1000.0f);
			//		// add movement 
			//		//AddMovementInput(this->GetActorUpVector(), -1.0f);
			//	}
			//}
			//else
			//{
			//	if (this->GetActorLocation().Z <= CharacterZAxis + 25.0f) {
			//		//SetCharacterMovementMode(EMovementMode::MOVE_Flying);
			//		//SetBrakingDecelerationFlying(1000.0f);
			//		// add movement 
			//		//AddMovementInput(this->GetActorUpVector(), 1.0f);

			//	}
			//}

			

		/*	if (FVector::Distance(this->GetActorLocation(), Ladder->GetDownMarkerComponent()->GetComponentLocation()) < 100.0f)
			{
				IsOnLadder = false;
				SetCharacterMovementMode(EMovementMode::MOVE_Walking);
				SetBrakingDecelerationFlying(0.0f);
			}*/
		}
	}
}

// Called to bind functionality to input
void AFPPCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPPCharacterBase::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPPCharacterBase::Look);

		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AFPPCharacterBase::Jump);

		//Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AFPPCharacterBase::Interact);
	}
}

void AFPPCharacterBase::SetLadder(ALadder* LadderParam)
{
	Ladder = LadderParam;
}

void AFPPCharacterBase::SetIsNearLadder(bool IsNearLadderParam)
{
	IsNearLadder = IsNearLadderParam;
}

void AFPPCharacterBase::SetIsOnLadder(bool IsOnLadderParam)
{
	IsOnLadder = IsOnLadderParam;
}

void AFPPCharacterBase::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		if (IsOnLadder)
		{ 
			SetCharacterMovementMode(EMovementMode::MOVE_Flying);
			SetBrakingDecelerationFlying(1000.0f);
			// add movement
			if (MovementVector.Y != 0.0f)
			{
				AddMovementInput(this->GetActorUpVector(), MovementVector.Y);
				//AddMovementInput(RightDirection, MovementVector.X);
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Velocity: %f"), MovementVector.Y));
			}
			/*else 
			{
				this->GetCharacterMovement()->Velocity.Z = 0.0f;
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Velocity: %f"), MovementVector.Y));
				AddMovementInput(this->GetActorUpVector(), 0.0f);
			}*/

			if (Ladder)
			{
				//SetCharacterGravityScale(0.0f);
				FRotator CharacterRot = this->GetActorRotation();
				FRotator LadderRot = Ladder->GetActorRotation();
				FRotator NewCharacterRot(CharacterRot.Pitch, CharacterRot.Roll, LadderRot.Yaw - 90);
				this->SetActorRotation(NewCharacterRot);

				FVector CharacterLoc = this->GetActorLocation();
				FVector LadderLoc = Ladder->GetActorLocation();
				FVector NewCharacterLoc(LadderLoc.X - FacingDistanceToObject, LadderLoc.Y, CharacterLoc.Z);
				this->SetActorLocation(NewCharacterLoc);
			}

			/*if (MovementVector.X != 0.0f) 
			{
				IsOnLadder = false;
				SetCharacterMovementMode(EMovementMode::MOVE_Walking);
				SetBrakingDecelerationFlying(0.0f);
			}*/
		}
		else
		{
			// get right vector 
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// add movement 
			AddMovementInput(ForwardDirection, MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
		}
		
	}
}

void AFPPCharacterBase::Look(const FInputActionValue& Value)
{

	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		if (!IsOnLadder)
		{
			AddControllerYawInput(LookAxisVector.X);
		}

		AddControllerPitchInput(LookAxisVector.Y);
		
	}
}

void AFPPCharacterBase::Interact()
{
	if (!IsNearLadder) return;

	if (!IsFacingToLadder) return;

	if (IsOnLadder)
	{
		IsOnLadder = false;
		SetCharacterMovementMode(EMovementMode::MOVE_Walking);
		SetBrakingDecelerationFlying(0.0f);
	}
	else
	{

		FRotator CharacterRot = this->GetActorRotation();
		FRotator LadderRot = Ladder->GetActorRotation();
		FRotator NewCharacterRot(CharacterRot.Pitch, CharacterRot.Roll, LadderRot.Yaw - 90);

		
		APlayerController* PlayerController = Cast<APlayerController>(this->GetController());

		if (PlayerController)
		{
			FRotator PlayerControllerRot(PlayerController->GetControlRotation().Pitch, NewCharacterRot.Yaw, PlayerController->GetControlRotation().Roll);
			PlayerController->SetControlRotation(PlayerControllerRot);
		}

		const FVector CharacterLoc = this->GetActorLocation();
		const FVector UpLoc = Ladder->GetUpMarkerComponent()->GetComponentLocation();
		const FVector DownLoc = Ladder->GetDownMarkerComponent()->GetComponentLocation();

		float UpDistance = FVector::Distance(CharacterLoc, UpLoc);
		float DownDistance = FVector::Distance(CharacterLoc, DownLoc);

		IsCharacterUpLadder = UpDistance < DownDistance ? true : false;

		CharacterZAxis = this->GetActorLocation().Z;
		IsOnLadder = true;
	}

	GetWorld()->GetTimerManager().SetTimer(CheckgroundTimerHandle, this, &AFPPCharacterBase::GetSideClosebyRayHits, 0.05f, true, 2.0f);
}

void AFPPCharacterBase::SetMaxWalkSpeed(float MaxWalkSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

void AFPPCharacterBase::SetCharacterMovementMode(EMovementMode MovementModeParam)
{
	this->GetCharacterMovement()->MovementMode = MovementModeParam; 
}

void AFPPCharacterBase::SetCharacterGravityScale(float GravityScaleParam)
{
	this->GetCharacterMovement()->GravityScale = GravityScaleParam;
}

void AFPPCharacterBase::SetBrakingDecelerationFlying(float BrakingDecelerationFlyingParam)
{
	this->GetCharacterMovement()->BrakingDecelerationFlying = BrakingDecelerationFlyingParam;
}

void AFPPCharacterBase::GetSideClosebyRayHits()
{
	
	
	FHitResult HitResult;
	static const FVector UpwardsOffset(0.0f, 0.0f, 40.0f);
	static const FVector RayMove(0.0f, 0.0f, -150.0f);
	const FVector ActorRightVector = this->GetActorRightVector();
	const FVector RayStart = this->GetActorLocation();
	const FVector RayEnd = RayStart + RayMove;

	UWorld* World = Owner->GetWorld();
	FCollisionQueryParams CollisionQuery;
	CollisionQuery.AddIgnoredActor(this);
	CollisionQuery.bReturnPhysicalMaterial = true;

	
	bool IsHit = World->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, ECC_Visibility, CollisionQuery);
	/*DrawDebugLine(
		GetWorld(),
		RayStart,
		RayEnd,
		FColor(255, 0, 0),
		false, 1, 0,
		12.333
	);*/
	if (IsHit) {
		//GEngine->AddOnScreenDebugMessage(-1, 8, FColor::Red, TEXT("Test message! %f"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: %f"), HitResult.Distance));
		if (HitResult.Distance < 120.0f) {
			IsOnLadder = false;
			SetCharacterMovementMode(EMovementMode::MOVE_Walking);
			SetBrakingDecelerationFlying(0.0f);
		}
	}
	
}