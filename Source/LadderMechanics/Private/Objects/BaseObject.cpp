// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/BaseObject.h"

#include "Characters/FPP/FPPPlayerControllerBase.h"
#include "Characters/FPP/FPPCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseObject::ABaseObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BaseBoxComponent"));
	//BaseBoxComponent->SetCollisionProfileName(TEXT("BlockAll"));
	BaseBoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BaseBoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RootComponent = BaseBoxComponent;

	BaseStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseStaticMeshComponent"));
	BaseStaticMeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
	BaseStaticMeshComponent->SetupAttachment(RootComponent);

	SocketNameL = "None";
	SocketNameR = "None";

}

// Called when the game starts or when spawned
void ABaseObject::BeginPlay()
{
	Super::BeginPlay();
	
	BaseBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseObject::OnColliderBeginOverlap);
	BaseBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseObject::OnColliderEndOverlap);
}

// Called every frame
void ABaseObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseObject::UseLeftInteracter()
{
	DisableGravity(SocketNameL);
	//bIsLeftInteracterTaken = true;
}

void ABaseObject::UseRightInteracter()
{
	DisableGravity(SocketNameR);
	//bIsRightInteracterTaken = true;
}

void ABaseObject::EnableGravity()
{
	if (this->GetAttachParentActor()) {
		AFPPCharacterBase* FPPCharacterBase = Cast<AFPPCharacterBase>(this->GetAttachParentActor());

		if (FPPCharacterBase) {
			this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			BaseStaticMeshComponent->SetSimulatePhysics(true);
			BaseStaticMeshComponent->SetCollisionProfileName(TEXT("PhysicsActor"));
			BaseStaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
			BaseStaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		}
	}
}

void ABaseObject::DisableGravity(FName Socket)
{
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Character) return;

	AFPPCharacterBase* FPPCharacterBase = Cast<AFPPCharacterBase>(Character);

	if (FPPCharacterBase) {
		BaseStaticMeshComponent->SetSimulatePhysics(false);
		BaseStaticMeshComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
		this->AttachToComponent(FPPCharacterBase->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
	}
}

void ABaseObject::OnColliderBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this) {

		AFPPPlayerControllerBase* FPPPlayerControllerBase = Cast<AFPPPlayerControllerBase>(OtherActor);
		if (FPPPlayerControllerBase) {
			//FPPGameModeBase->SetIsPlayerNear(true);
		}
	}
}

void ABaseObject::OnColliderEndOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this) {

		AFPPPlayerControllerBase* FPPPlayerControllerBase = Cast<AFPPPlayerControllerBase>(OtherActor);
		if (FPPPlayerControllerBase) {
			//FPPGameModeBase->SetIsPlayerNear(false);
		}
	}
}

