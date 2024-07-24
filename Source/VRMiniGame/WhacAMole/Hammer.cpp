#include "Hammer.h"
#include "Grippables/GrippableStaticMeshComponent.h"
#include "Grippables/HandSocketComponent.h"
#include "VRPlayerController.h"
#include "VRCharacter.h"
#include "Components/SplineComponent.h"

AHammer::AHammer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UOptionalRepStaticMeshComponent>(TEXT("StaticMeshComponent0")))
{
	PrimaryActorTick.bCanEverTick = true;

	/*
	GripLine = CreateDefaultSubobject<USplineComponent>(TEXT("GripLine"));
	GripLine->SetupAttachment(RootComponent);

	WepOrientation = CreateDefaultSubobject<USceneComponent>(TEXT("WepOrientation"));
	WepOrientation->SetupAttachment(RootComponent);
	GripRotation = CreateDefaultSubobject<UHandSocketComponent>(TEXT("GripRotation"));
	GripRotation->SetupAttachment(RootComponent);
	ReverseGripRotation = CreateDefaultSubobject<UHandSocketComponent>(TEXT("ReverseGripRotation"));
	ReverseGripRotation->SetupAttachment(RootComponent);*/
}

void AHammer::BeginPlay()
{
	Super::BeginPlay();
}

bool AHammer::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return false;
}

bool AHammer::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return false;
}

bool AHammer::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return false;
}

void AHammer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHammer::OnRep_Owner()
{
	Super::OnRep_Owner();
	if (Owner == nullptr)
	{
		OwnerCharacter = nullptr;
		OwnerController = nullptr;
	}
	else
	{
		OwnerCharacter = OwnerCharacter == nullptr ? Cast<AVRCharacter>(Owner) : OwnerCharacter;
	}
}

void AHammer::Dropped()
{
	SetOwner(nullptr);
	OwnerCharacter = nullptr;
	OwnerController = nullptr;
}

