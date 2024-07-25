#include "GolfField.h"
#include "GolfBall.h"
#include "VRMiniGame/Player/MiniGamePlayerState.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

AGolfField::AGolfField()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	PointsCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("PointsCollider"));
	PointsCollider->SetupAttachment(Mesh);
	PointsCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void AGolfField::BeginPlay()
{
	Super::BeginPlay();

	PointsCollider->OnComponentBeginOverlap.AddDynamic(this, &AGolfField::OnBeginOverlap);
}

void AGolfField::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			"Colidiu"
		);
	}
	if (OtherActor == nullptr || !OtherActor) return;

	AGolfBall* GolfBall = Cast<AGolfBall>(OtherActor);

	if (GolfBall == nullptr || !GolfBall) return;

	if (GolfBall->OwningPlayer == nullptr || !GolfBall->OwningPlayer) return;

	GolfBall->OwningPlayer->AddToScore(1.f);
}

