#include "MiniGamePlayerState.h"
#include "VRMiniGame/Player/GameState/MiniGameGameState.h"
#include "VRMiniGame/Player/GameModes/MiniGameGameModeBase.h"
#include "VRMiniGame/UI/WorldWidgetActor.h"
#include "Kismet/GameplayStatics.h"

void AMiniGamePlayerState::BeginPlay()
{
	AMiniGameGameState* GameState = Cast<AMiniGameGameState>(UGameplayStatics::GetGameState(this));
	if (GameState)
	{
		GameState->AddPlayerToPlayerScores(this);
	}
	ServerCheckMatchState();

}

void AMiniGamePlayerState::AddToScore(float ScoreAmount)
{
	SetScore(GetScore() + ScoreAmount);

	ScoreUpdated.Broadcast(GetScore());
}

float AMiniGamePlayerState::GetServerTime()
{
	if (HasAuthority()) return GetWorld()->GetTimeSeconds();
	else return GetWorld()->GetTimeSeconds() + ClientServerDelta;
}

void AMiniGamePlayerState::ClientJoinMidgame_Implementation(float MiniGameStart, float LevelStarting)
{
	MiniGameStartTime = MiniGameStart;
	LevelStartingTime = LevelStarting; 

	// chama função
}

void AMiniGamePlayerState::ServerCheckMatchState_Implementation()
{
	AMiniGameGameModeBase* GameMode = Cast<AMiniGameGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		MiniGameStartTime = GameMode->MiniGameStartTime;
		LevelStartingTime = GameMode->LevelStartingTime;
		ClientJoinMidgame(MiniGameStartTime, LevelStartingTime);
	}
}

void AMiniGamePlayerState::ServerRequestServerTime_Implementation(float TimeOfClientRequest)
{
	float ServerTimeOfReceipt = GetWorld()->GetTimeSeconds();

	ClientReportServerTime(TimeOfClientRequest, ServerTimeOfReceipt);
}

void AMiniGamePlayerState::ClientReportServerTime_Implementation(float TimeOfClientRequest, float TimeServerReceivedClientRequest)
{
	float RoundTripTime = GetWorld()->GetTimeSeconds() - TimeOfClientRequest;
	SingleTripTime = 0.5f * RoundTripTime;
	float CurrentServerTime = TimeServerReceivedClientRequest + SingleTripTime;
	ClientServerDelta = CurrentServerTime - GetWorld()->GetTimeSeconds();
}
