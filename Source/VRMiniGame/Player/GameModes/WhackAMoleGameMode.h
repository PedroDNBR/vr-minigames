#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "WhackAMoleGameMode.generated.h"

UCLASS()
class VRMINIGAME_API AWhackAMoleGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void HandleSeamlessTravelPlayer(AController*& C) override;

};
