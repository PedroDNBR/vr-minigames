#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MiniGameGameModeBase.generated.h"

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

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float MiniGameStartTime = 10.f;

	float LevelStartingTime = 0.f;
	float CountdownTime = 0.f;

	bool bStartCountdown = false;


private:
	int32 LoadedPlayersQuantity;

};
