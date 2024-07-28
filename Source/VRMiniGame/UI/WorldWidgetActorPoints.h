// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldWidgetActor.h"
#include "WorldWidgetActorPoints.generated.h"

/**
 * 
 */
UCLASS()
class VRMINIGAME_API AWorldWidgetActorPoints : public AWorldWidgetActor
{
	GENERATED_BODY()
public:
	AWorldWidgetActorPoints();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxPlayerDetector;

	void UpdateUIScore(int32 Score);

protected:
	UPROPERTY(ReplicatedUsing = OnRep_UpdateUIScore)
	int32 CurrentScore = 0;

	UFUNCTION()
	void OnRep_UpdateUIScore(int32 Score);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastUpdateUIScore(int32 Score);

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void GetScoreFromOverlappingActor(AActor* OtherActor);

private:
	FTimerHandle IncreaseBoxSizeTimer;
	FVector StartingBoxSize;
	void SetBoxSizeToDefault();
};
