#pragma once

#include "CoreMinimal.h"
#include "Misc/VRPlayerStart.h"
#include "MiniGamePlayerSpawn.generated.h"

UCLASS()
class VRMINIGAME_API AMiniGamePlayerSpawn : public AVRPlayerStart
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	bool bAlreadySpawned = false;
	
};
