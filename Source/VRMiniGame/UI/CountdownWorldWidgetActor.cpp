#include "CountdownWorldWidgetActor.h"
#include "VRMiniGame/Player/GameModes/MiniGameGameModeBase.h"
#include "VRMiniGame/Player/MiniGamePlayerState.h"
#include "Widgets/InGame/TimeToStartMiniGameWidget.h"
#include "Components/TextBlock.h" 
#include "Components/WidgetComponent.h" 
#include "VRCharacter.h"
#include "Kismet/GameplayStatics.h"

void ACountdownWorldWidgetActor::BeginPlay()
{
	Super::BeginPlay();

	if (PointsWidget == nullptr || !PointsWidget) return;

	if (PointsWidget->GetWidget() == nullptr || !PointsWidget->GetWidget()) return;
	TimeWidget = Cast<UTimeToStartMiniGameWidget>(PointsWidget->GetWidget());
}

void ACountdownWorldWidgetActor::SetOwnerActors()
{
	OwnerCharacter = Cast<AVRCharacter>(GetOwner());
	if (OwnerCharacter == nullptr || !OwnerCharacter) return;

	if (OwnerCharacter->GetPlayerState() == nullptr || !OwnerCharacter->GetPlayerState()) return;

	OwnerPlayerState = Cast<AMiniGamePlayerState>(OwnerCharacter->GetPlayerState());

	if (OwnerPlayerState == nullptr || !OwnerPlayerState) return;

	OwnerPlayerState->ServerRequestServerTime(GetWorld()->GetTimeSeconds());
}

void ACountdownWorldWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (OwnerPlayerState == nullptr || !OwnerPlayerState)
	{
		SetOwnerActors();
	}
	if (OwnerPlayerState == nullptr || !OwnerPlayerState) return;

	float TimeLeft = 0.f;
	TimeLeft = OwnerPlayerState->MiniGameStartTime - OwnerPlayerState->GetServerTime() + OwnerPlayerState->LevelStartingTime;

	if (TimeLeft < 5)
	{
		if (TimeWidget == nullptr || !TimeWidget) return;
		TimeWidget->Time->SetText(
			FText::FromString(
				FString::Printf(
					TEXT("%i"), FMath::CeilToInt(TimeLeft)
				)
			)
		);
	}

	if (TimeLeft <= -1)
	{
		Destroy();
	}
	
}
