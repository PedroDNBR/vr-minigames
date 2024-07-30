#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldWidgetActor.generated.h"


UCLASS()
class VRMINIGAME_API AWorldWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AWorldWidgetActor();

	UPROPERTY(EditAnywhere)
	class USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* PointsWidget;
};
