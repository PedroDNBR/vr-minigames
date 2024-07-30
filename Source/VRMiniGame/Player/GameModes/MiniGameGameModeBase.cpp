#include "MiniGameGameModeBase.h"
#include "VRMiniGame/Game/MiniGameGameInstance.h"

void AMiniGameGameModeBase::PlayerLodaded()
{
	ServerPlayerLodaded();
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
	}
}
