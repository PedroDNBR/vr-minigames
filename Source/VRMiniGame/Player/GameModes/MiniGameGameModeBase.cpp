#include "MiniGameGameModeBase.h"
#include "VRMiniGame/Game/MiniGameGameInstance.h"

void AMiniGameGameModeBase::PlayerLodaded()
{
	ServerPlayerLodaded();
}

void AMiniGameGameModeBase::StartMiniGameMatch()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			"StartMiniGameMatch"
		);
	}

	bStartCountdown = false;
}

void AMiniGameGameModeBase::Tick(float DeltaTime)
{
	if (!bStartCountdown) return;

	float TimeLeft = .0f;
	TimeLeft = MiniGameStartTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;

	if (TimeLeft <= 0)
	{
		StartMiniGameMatch();
	}
}

void AMiniGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	LevelStartingTime = GetWorld()->GetTimeSeconds();
}

void AMiniGameGameModeBase::ServerPlayerLodaded_Implementation()
{
	UMiniGameGameInstance* MiniGameGameInstance = Cast<UMiniGameGameInstance>(GetGameInstance());

	LoadedPlayersQuantity++;

	if (MiniGameGameInstance == nullptr || !MiniGameGameInstance) return;

	if (LoadedPlayersQuantity >= MiniGameGameInstance->PlayersInGameWhenMatchStarted)
	{
		bStartCountdown = true;
		StartTimer.Broadcast();
	}
}
