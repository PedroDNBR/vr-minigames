#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "VRPlayerController.h"
#include "VRCharacter.h"
#include "MiniGamePlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreUpdated, int32, Score);

UCLASS()
class VRMINIGAME_API AMiniGamePlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	void AddToScore(float ScoreAmount);
	FScoreUpdated ScoreUpdated;

	UFUNCTION(BlueprintCallable)
	float GetServerTime();

	float ClientServerDelta = 0.f;
	float SingleTripTime = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float MiniGameStartTime = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float LevelStartingTime = 0.f;

	UFUNCTION(Server, Reliable)
	void ServerRequestServerTime(float TimeOfClientRequest);

	UFUNCTION(Client, Reliable)
	void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);

	UFUNCTION(Server, Reliable)
	void ServerCheckMatchState();

	UFUNCTION(Client, Reliable)
	void ClientJoinMidgame(float MiniGameStart, float LevelStarting);

private:
	UPROPERTY()
	class AVRCharacter* Character;
	UPROPERTY()
	class AVRPlayerController* Controller;

};
