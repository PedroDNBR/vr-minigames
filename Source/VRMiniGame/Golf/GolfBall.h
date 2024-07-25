// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GolfBall.generated.h"

UCLASS()
class VRMINIGAME_API AGolfBall : public AActor
{
	GENERATED_BODY()
	
public:	
	AGolfBall();
	class AMiniGamePlayerState* OwningPlayer;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

};
