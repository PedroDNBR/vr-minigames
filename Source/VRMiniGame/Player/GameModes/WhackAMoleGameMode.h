#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "WhackAMoleGameMode.generated.h"

UCLASS()
class VRMINIGAME_API AWhackAMoleGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void PlayerLodaded();

	UFUNCTION(Server, Reliable)
	void ServerPlayerLodaded();

private:
	int32 LoadedPlayersQuantity;

};
