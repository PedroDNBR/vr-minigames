#pragma once

#include "CoreMinimal.h"
#include "MiniGameGameModeBase.h"
#include "WhackAMoleGameMode.generated.h"

UCLASS()
class VRMINIGAME_API AWhackAMoleGameMode : public AMiniGameGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartMiniGameMatch() override;

};
