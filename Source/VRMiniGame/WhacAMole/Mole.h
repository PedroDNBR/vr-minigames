// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mole.generated.h"

UENUM(BlueprintType)
enum class EMoleState : uint8
{
	EMS_Idle UMETA(DisplayName = "Idle"),
	EMS_Ascended UMETA(DisplayName = "Ascended"),
	EMS_Ascending UMETA(DisplayName = "Ascending"),
	EMS_Descending UMETA(DisplayName = "Descending"),
	EMS_Descended UMETA(DisplayName = "Descended"),
	EMS_Hitted UMETA(DisplayName = "Hitted"),
	EMS_MAX UMETA(DisplayName = "MAX"),
};

UCLASS()
class VRMINIGAME_API AMole : public AActor
{
	GENERATED_BODY()

public:
	AMole();
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void StartMole();

protected:
	virtual void BeginPlay() override;
	void Ascend();
	void Ascended();
	void Descend();
	void Descended();
	void Hitted();

	void AscendMoleMovement(float DeltaTime);
	void DescendMoleMovement(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

private:
	class USceneComponent* Root;

	UPROPERTY(Replicated, VisibleAnywhere)
	EMoleState State;

	UPROPERTY(EditAnywhere)
	int8 AscendHeight = 8;

	int8 StartHeight;

	UPROPERTY(EditAnywhere)
	float Speed = 2.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FTimerHandle AscendTimer;


public:
	FORCEINLINE EMoleState GetState() { return State; }
	FORCEINLINE void SetState(EMoleState NewState) { State = NewState; }
};
