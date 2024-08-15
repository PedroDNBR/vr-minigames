#pragma once

#include "CoreMinimal.h"
#include "WorldWidgetActor.h"
#include "CountdownWorldWidgetActor.generated.h"

UCLASS()
class VRMINIGAME_API ACountdownWorldWidgetActor : public AWorldWidgetActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString InitialMessage;
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

	class AVRCharacter* OwnerCharacter;
	class AMiniGamePlayerState* OwnerPlayerState;

	void SetOwnerActors();

private:
	class UTimeToStartMiniGameWidget* TimeWidget;

};
