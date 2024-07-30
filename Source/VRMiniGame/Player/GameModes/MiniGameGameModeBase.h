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

private:
	int32 LoadedPlayersQuantity;

};
