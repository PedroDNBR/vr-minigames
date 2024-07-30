#pragma once

#include "CoreMinimal.h"
#include "AdvancedFriendsGameInstance.h"
#include "MiniGameGameInstance.generated.h"

UCLASS()
class VRMINIGAME_API UMiniGameGameInstance : public UAdvancedFriendsGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayersInGameWhenMatchStarted = 0;
	
};
