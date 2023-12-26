// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ladder.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class AFPPCharacterBase;
class USceneComponent;

UCLASS()
class LADDERMECHANICS_API ALadder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALadder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FORCEINLINE USceneComponent* GetUpMarkerComponent() const { return UpMarkerComponent; }
	FORCEINLINE USceneComponent* GetDownMarkerComponent() const { return DownMarkerComponent; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LadderMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* LadderBoxComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USceneComponent* UpMarkerComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USceneComponent* DownMarkerComponent = nullptr;

	FTimerHandle ResetGravityScaleTimerHandle;

	UFUNCTION()
	void ResetGravityScale(AFPPCharacterBase* FPPCharacterBase);
};
