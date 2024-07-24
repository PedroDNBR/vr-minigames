// Fill out your copyright notice in the Description page of Project Settings.

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

private:
	UPROPERTY()
	class AVRCharacter* Character;
	UPROPERTY()
	class AVRPlayerController* Controller;

};
