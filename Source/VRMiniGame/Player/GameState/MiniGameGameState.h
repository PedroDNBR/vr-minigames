// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MiniGameGameState.generated.h"

/**
 * 
 */
UCLASS()
class VRMINIGAME_API AMiniGameGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;

	void AddPlayerToPlayerScores(class AMiniGamePlayerState* PlayerState);

	UPROPERTY(Replicated)
	TArray<class AMiniGamePlayerState*> PlayerScores;

	UPROPERTY(EditDefaultsOnly)
	TMap<FString, bool> ModesAvailable;

	void StartRandomMiniGame();
};
