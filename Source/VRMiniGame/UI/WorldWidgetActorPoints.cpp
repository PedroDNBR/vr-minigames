#include "WorldWidgetActorPoints.h"
#include "VRCharacter.h"
#include "VRPlayerController.h"
#include "VRMiniGame/UI/Widgets/InGame/PlayerPointsWidget.h"
#include "VRMiniGame/Player/MiniGamePlayerState.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"

AWorldWidgetActorPoints::AWorldWidgetActorPoints()
{
	BoxPlayerDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxPlayerDetector"));
	BoxPlayerDetector->SetupAttachment(RootComponent);
}

void AWorldWidgetActorPoints::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWorldWidgetActorPoints, CurrentScore);
}

void AWorldWidgetActorPoints::UpdateUIScore(int32 Score)
{
	if (PointsWidget == nullptr || !PointsWidget) return;

	UPlayerPointsWidget* PlayerPointsWidget = Cast<UPlayerPointsWidget>(PointsWidget->GetWidget());

	if (PlayerPointsWidget == nullptr || !PlayerPointsWidget) return;

	FString ScoreString = FString::Printf(TEXT("%i"), Score);

	PlayerPointsWidget->Score->SetText(FText::FromString(ScoreString));
}

void AWorldWidgetActorPoints::OnRep_UpdateUIScore(int32 Score)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			"Replicou"
		);
	}

	UpdateUIScore(Score);
}

void AWorldWidgetActorPoints::MulticastUpdateUIScore_Implementation(int32 Score)
{
	UpdateUIScore(Score);
}

void AWorldWidgetActorPoints::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority()) return;

	TArray<class AActor*> OverlappingActors;

	BoxPlayerDetector->GetOverlappingActors(OverlappingActors);

	StartingBoxSize = BoxPlayerDetector->GetScaledBoxExtent();

	BoxPlayerDetector->SetBoxExtent(FVector(0, 0, 0));

	GetWorldTimerManager().SetTimer(
		IncreaseBoxSizeTimer,
		this,
		&AWorldWidgetActorPoints::SetBoxSizeToDefault,
		2.f
	);

	if (OverlappingActors.Num() > 0)
	{
		for (int32 i = 0; i < OverlappingActors.Num(); i++)
		{
			GetScoreFromOverlappingActor(OverlappingActors[i]);
		}
	}

	BoxPlayerDetector->OnComponentBeginOverlap.AddDynamic(this, &AWorldWidgetActorPoints::OnBeginOverlap);
}

void AWorldWidgetActorPoints::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetScoreFromOverlappingActor(OtherActor);
}

void AWorldWidgetActorPoints::GetScoreFromOverlappingActor(AActor* OtherActor)
{
	if (!HasAuthority()) return;

	if (OtherActor == nullptr || !OtherActor) return;

	if (PointsWidget == nullptr || !PointsWidget) return;

	UPlayerPointsWidget* PlayerPointsWidget = Cast<UPlayerPointsWidget>(PointsWidget->GetWidget());
	if (PlayerPointsWidget == nullptr || !PlayerPointsWidget) return;

	AVRCharacter* Character = Cast<AVRCharacter>(OtherActor);
	if (Character == nullptr || !Character) return;

	if (Character->Controller == nullptr || !Character->Controller) return;

	AMiniGamePlayerState* PlayerState = Character->Controller->GetPlayerState<AMiniGamePlayerState>();

	if (PlayerState == nullptr || !PlayerState) return;

	PlayerState->ScoreUpdated.RemoveAll(this);
	PlayerState->ScoreUpdated.AddDynamic(this, &AWorldWidgetActorPoints::MulticastUpdateUIScore);

	CurrentScore = (int32)PlayerState->GetScore();
	MulticastUpdateUIScore(CurrentScore);
	UpdateUIScore(CurrentScore);
}

void AWorldWidgetActorPoints::SetBoxSizeToDefault()
{
	BoxPlayerDetector->SetBoxExtent(StartingBoxSize);
}
