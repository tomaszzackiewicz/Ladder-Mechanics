// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseObject.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class LADDERMECHANICS_API ABaseObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UBoxComponent* GetBaseBoxComponent() const { return BaseBoxComponent; }

	FORCEINLINE class UStaticMeshComponent* GetBaseStaticMeshComponent() const { return BaseStaticMeshComponent; }

	virtual void UseLeftInteracter();

	virtual void UseRightInteracter();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseObject", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BaseBoxComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseObject", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseStaticMeshComponent = nullptr;

	class ASurvivor* CurrentSurvivor;

	virtual void EnableGravity();

	virtual void DisableGravity(FName Socket);

	UFUNCTION()
	void OnColliderBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnColliderEndOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FName SocketNameL;

	FName SocketNameR;

};
