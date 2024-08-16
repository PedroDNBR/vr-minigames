#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MiniGameGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartTimer);

UCLASS()
class VRMINIGAME_API AMiniGameGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void PlayerLodaded();

	UFUNCTION(Server, Reliable)
	void ServerPlayerLodaded();

	virtual void StartMiniGameMatch();

	UPROPERTY(EditAnywhere)
	float MiniGameStartTime = 10.f;

	float LevelStartingTime = 0.f;

	UPROPERTY(BlueprintAssignable)
	FStartTimer StartTimer;

	bool bStartCountdown = false;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	int32 LoadedPlayersQuantity;


public:
	FORCEINLINE bool GetStartCountdown() { return bStartCountdown; }
};
