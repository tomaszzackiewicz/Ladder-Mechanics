// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Ladder.h"

#include "Characters/FPP/FPPCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ALadder::ALadder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LadderMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LadderMeshComponent"));
	SetRootComponent(LadderMeshComponent);

	LadderBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("LadderBoxComponent"));
	LadderBoxComponent->SetupAttachment(LadderMeshComponent);

	UpMarkerComponent = CreateDefaultSubobject<USceneComponent>(TEXT("UpMarkerComponent"));
	UpMarkerComponent->SetupAttachment(LadderMeshComponent);

	DownMarkerComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DownMarkerComponent"));
	DownMarkerComponent->SetupAttachment(LadderMeshComponent);
}

// Called when the game starts or when spawned
void ALadder::BeginPlay()
{
	Super::BeginPlay();

	LadderBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ALadder::OnBoxBeginOverlap);
	LadderBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ALadder::OnBoxEndOverlap);
	
}

// Called every frame
void ALadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALadder::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this)) 
	{
		AFPPCharacterBase* FPPCharacterBase = Cast<AFPPCharacterBase>(OtherActor);
		if (FPPCharacterBase)
		{
			FPPCharacterBase->SetLadder(this);
			FPPCharacterBase->SetIsNearLadder(true);
		}
	}
}

void ALadder::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		AFPPCharacterBase* FPPCharacterBase = Cast<AFPPCharacterBase>(OtherActor);
		if (FPPCharacterBase)
		{
			FPPCharacterBase->SetLadder(nullptr);
			FPPCharacterBase->SetIsNearLadder(false);
			FPPCharacterBase->SetIsOnLadder(false);

			FPPCharacterBase->SetCharacterMovementMode(EMovementMode::MOVE_Walking);
			FPPCharacterBase->SetCharacterGravityScale(0.0f);
			FPPCharacterBase->SetBrakingDecelerationFlying(0.0f);

			FTimerHandle UniqueHandle;
			FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject(this, &ALadder::ResetGravityScale, FPPCharacterBase);
			GetWorldTimerManager().SetTimer(UniqueHandle, RespawnDelegate, 0.2f, false);
		}
	}
}

void ALadder::ResetGravityScale(AFPPCharacterBase* FPPCharacterBase)
{
	FPPCharacterBase->SetCharacterGravityScale(1.75f);
}

