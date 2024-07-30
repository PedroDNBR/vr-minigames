#include "MiniGameGameState.h"
#include "VRMiniGame/Player/MiniGamePlayerState.h"
#include "Net/UnrealNetwork.h"
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


	World->ServerTravel(
		MapName.ToString()
	);
}
