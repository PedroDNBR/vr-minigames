#include "MiniGameGameState.h"
#include "MiniGamePlayerState.h"
#include "Net/UnrealNetwork.h"

void AMiniGameGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AMiniGameGameState, PlayerScores);
}

void AMiniGameGameState::AddPlayerToPlayerScores(AMiniGamePlayerState* PlayerState)
{
	PlayerScores.AddUnique(PlayerState);
}
