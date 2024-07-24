#include "TestGripDestructible.h"

ATestGripDestructible::ATestGripDestructible()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATestGripDestructible::BeginPlay()
{
	Super::BeginPlay();
}

void ATestGripDestructible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

