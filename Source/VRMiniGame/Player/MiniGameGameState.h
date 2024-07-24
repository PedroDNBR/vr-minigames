#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MiniGamePlayerState.h"
#include "MiniGameGameState.generated.h"

UCLASS()
class VRMINIGAME_API AMiniGameGameState : public AGameState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void AddPlayerToPlayerScores(AMiniGamePlayerState* PlayerState);

	UPROPERTY(Replicated)
	TArray<class AMiniGamePlayerState*> PlayerScores;
	
};
