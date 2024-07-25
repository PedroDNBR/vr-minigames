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

	SpawnerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnerCollider"));
	SpawnerCollider->SetupAttachment(Mesh);
	SpawnerCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void AGolfField::BeginPlay()
{
	Super::BeginPlay();

	PointsCollider->OnComponentBeginOverlap.AddDynamic(this, &AGolfField::OnBeginOverlap);
	SpawnerCollider->OnComponentEndOverlap.AddDynamic(this, &AGolfField::OnEndOverlap);

	SpawnGolfBall();
}

void AGolfField::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr || !OtherActor) return;

	AGolfBall* GolfBall = Cast<AGolfBall>(OtherActor);

	if (GolfBall == nullptr || !GolfBall) return;

	if (GolfBall->OwningPlayer == nullptr || !GolfBall->OwningPlayer) return;

	GolfBall->OwningPlayer->AddToScore(1.f);

	GolfBall->Destroy();
}

void AGolfField::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == nullptr || !OtherActor) return;

	AGolfBall* GolfBall = Cast<AGolfBall>(OtherActor);

	if (GolfBall == nullptr || !GolfBall) return;

	SpawnGolfBall();
}

void AGolfField::SpawnGolfBall()
{
	UWorld* World = GetWorld();

	if (World == nullptr || !World) return;

	if (GolfBallClass == nullptr || !GolfBallClass) return;

	World->SpawnActor<AGolfBall>(
		GolfBallClass,
		SpawnerCollider->GetComponentTransform()
	);
}

