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
}

void AMiniGameGameModeBase::Tick(float DeltaTime)
{
	if (bStartCountdown)
	{
		CountdownTime = MiniGameStartTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (GEngine && CountdownTime <= 6)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				2.f,
				FColor::Green,
				FString::Printf(TEXT("%f"), CountdownTime)
			);
		}
		if (CountdownTime <= 0.f)
		{
			StartMiniGameMatch();
			bStartCountdown = false;
		}
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
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Green,
				"Bateu a quatidade"
			);
		}
		bStartCountdown = true;
	}
}
