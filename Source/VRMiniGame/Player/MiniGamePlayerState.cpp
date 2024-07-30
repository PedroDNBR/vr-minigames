#include "MiniGamePlayerState.h"
#include "VRMiniGame/Player/GameState/MiniGameGameState.h"
#include "Kismet/GameplayStatics.h"

void AMiniGamePlayerState::BeginPlay()
{
	AMiniGameGameState* GameState = Cast<AMiniGameGameState>(UGameplayStatics::GetGameState(this));
	if (GameState)
	{
		GameState->AddPlayerToPlayerScores(this);
	}
}

void AMiniGamePlayerState::AddToScore(float ScoreAmount)
{
	SetScore(GetScore() + ScoreAmount);

	ScoreUpdated.Broadcast(GetScore());

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			FString::Printf(TEXT("Score: %f"), GetScore())
		);
	}
}
