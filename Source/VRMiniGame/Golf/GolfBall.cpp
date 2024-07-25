#include "GolfBall.h"
#include "VRMiniGame/Player/MiniGamePlayerState.h"
#include "Components/StaticMeshComponent.h"

AGolfBall::AGolfBall()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(true);
}

void AGolfBall::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	if (World)
	{
		AMiniGamePlayerState* PlayerState = Cast<AMiniGamePlayerState>(World->GetFirstPlayerController()->PlayerState);

		if (PlayerState)
		{
			OwningPlayer = PlayerState;
		}
	}
}


