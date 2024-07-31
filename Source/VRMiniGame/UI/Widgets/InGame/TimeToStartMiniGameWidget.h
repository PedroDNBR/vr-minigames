#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimeToStartMiniGameWidget.generated.h"

UCLASS()
class VRMINIGAME_API UTimeToStartMiniGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Time;
};
