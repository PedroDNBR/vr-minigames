#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestGripDestructible.generated.h"

UCLASS()
class VRMINIGAME_API ATestGripDestructible : public AActor
{
	GENERATED_BODY()
	
public:	
	ATestGripDestructible();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
