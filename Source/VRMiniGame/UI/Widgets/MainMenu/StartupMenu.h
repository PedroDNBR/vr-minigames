#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartupMenu.generated.h"

UCLASS()
class VRMINIGAME_API UStartupMenu : public UUserWidget
{
	GENERATED_BODY()
	
public: 
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	class UButton* ServerList;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UButton* Settings;

	UPROPERTY(meta = (BindWidget))
	UButton* Quit;

private:
	UFUNCTION()
	void QuitGame();

};
