// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Items/Sextant.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

ASextant::ASextant()
{

	AlidadeStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AlidadeStaticMeshComponent"));
	AlidadeStaticMeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
	AlidadeStaticMeshComponent->SetupAttachment(BaseStaticMeshComponent);

	MicrometerStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MicrometerStaticMeshComponent"));
	MicrometerStaticMeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
	MicrometerStaticMeshComponent->SetupAttachment(AlidadeStaticMeshComponent);


	HighSetOfFiltersComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HighSetOfFiltersComponent"));
	HighSetOfFiltersComponent->SetupAttachment(BaseStaticMeshComponent);

	LowSetOfFiltersComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LowSetOfFiltersComponent"));
	LowSetOfFiltersComponent->SetupAttachment(BaseStaticMeshComponent);


	HighFilter1StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HighFilter1StaticMeshComponent"));
	HighFilter1StaticMeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
	HighFilter1StaticMeshComponent->SetupAttachment(HighSetOfFiltersComponent);

	HighFilter2StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HighFilter2StaticMeshComponent"));
	HighFilter2StaticMeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
	HighFilter2StaticMeshComponent->SetupAttachment(HighSetOfFiltersComponent);

	HighFilter3StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HighFilter3StaticMeshComponent"));
	HighFilter3StaticMeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
	HighFilter3StaticMeshComponent->SetupAttachment(HighSetOfFiltersComponent);


	LowFilter1StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LowFilter1StaticMeshComponent"));
	LowFilter1StaticMeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
	LowFilter1StaticMeshComponent->SetupAttachment(LowSetOfFiltersComponent);

	LowFilter2StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LowFilter2StaticMeshComponent"));
	LowFilter2StaticMeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
	LowFilter2StaticMeshComponent->SetupAttachment(LowSetOfFiltersComponent);

	LowFilter3StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LowFilter3StaticMeshComponent"));
	LowFilter3StaticMeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
	LowFilter3StaticMeshComponent->SetupAttachment(LowSetOfFiltersComponent);
}