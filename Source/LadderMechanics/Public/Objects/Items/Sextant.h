// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Items/BaseItem.h"
#include "Sextant.generated.h"

class USceneComponent;
class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class LADDERMECHANICS_API ASextant : public ABaseItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASextant();

	FORCEINLINE class UStaticMeshComponent* GetMicrometerStaticMeshComponent() const { return MicrometerStaticMeshComponent; }

	FORCEINLINE class UStaticMeshComponent* GetAlidadeStaticMeshComponent() const { return AlidadeStaticMeshComponent; }

	FORCEINLINE class USceneComponent* GetHighSetOfFiltersComponent() const { return HighSetOfFiltersComponent; }

	FORCEINLINE class USceneComponent* GetLowSetOfFiltersComponent() const { return LowSetOfFiltersComponent; }

	FORCEINLINE class UStaticMeshComponent* GetHighFilter1StaticMeshComponent() const { return HighFilter1StaticMeshComponent; }

	FORCEINLINE class UStaticMeshComponent* GetHighFilter2StaticMeshComponent() const { return HighFilter2StaticMeshComponent; }

	FORCEINLINE class UStaticMeshComponent* GetHighFilter3StaticMeshComponent() const { return HighFilter3StaticMeshComponent; }

	FORCEINLINE class UStaticMeshComponent* GetLowFilter1StaticMeshComponent() const { return LowFilter1StaticMeshComponent; }

	FORCEINLINE class UStaticMeshComponent* GetLowFilter2StaticMeshComponent() const { return LowFilter2StaticMeshComponent; }

	FORCEINLINE class UStaticMeshComponent* GetLowFilter3StaticMeshComponent() const { return LowFilter3StaticMeshComponent; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sextant", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MicrometerStaticMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sextant", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* AlidadeStaticMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sextant", meta = (AllowPrivateAccess = "true"))
	USceneComponent* HighSetOfFiltersComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sextant", meta = (AllowPrivateAccess = "true"))
	USceneComponent* LowSetOfFiltersComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sextant", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HighFilter1StaticMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sextant", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HighFilter2StaticMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sextant", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HighFilter3StaticMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sextant", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LowFilter1StaticMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sextant", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LowFilter2StaticMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sextant", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LowFilter3StaticMeshComponent = nullptr;
	
};
