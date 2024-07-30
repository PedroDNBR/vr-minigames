#include "MiniGameGameState.h"
#include "VRMiniGame/Player/MiniGamePlayerState.h"
#include "VRMiniGame/Game/MiniGameGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/GameMode.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

void AMiniGameGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMiniGameGameState, PlayerScores);
}

void AMiniGameGameState::AddPlayerToPlayerScores(AMiniGamePlayerState* PlayerState)
{
	PlayerScores.AddUnique(PlayerState);
}

void AMiniGameGameState::StartRandomMiniGame()
{
	UWorld* World = GetWorld();
	if (World == nullptr || !World) return;

	int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, ModesAvailable.Num() - 1);

	TArray<FString> MapNameStrings;

	ModesAvailable.GenerateKeyArray(MapNameStrings);

	FName MapName = FName(MapNameStrings[RandomIndex]);

	ModesAvailable[MapNameStrings[RandomIndex]] = true;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			MapName.ToString()
		);
	}
	// UGameplayStatics::OpenLevel(this, MapName, false, "listen");

	AGameMode* GameMode = GetWorld()->GetAuthGameMode<AGameMode>();

	if (GameMode == nullptr || !GameMode) return;

	UGameInstance* GameInstance = GetGameInstance();

	if (GameInstance == nullptr || !GameInstance) return;

	UMiniGameGameInstance* MiniGameGameInstance = Cast<UMiniGameGameInstance>(GameInstance);

	MiniGameGameInstance->PlayersInGameWhenMatchStarted = GameMode->GetNumPlayers();

	World->ServerTravel(
		MapName.ToString()
	);
}
