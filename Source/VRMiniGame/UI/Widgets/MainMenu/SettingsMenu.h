#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsMenu.generated.h"

UENUM(BlueprintType)
enum EQuality : uint8
{
	EQ_Low = 0 UMETA(DisplayName = "Low"),
	EQ_Medium = 1 UMETA(DisplayName = "Medium"),
	EQ_High = 2 UMETA(DisplayName = "High"),
	EQ_Epic = 3 UMETA(DisplayName = "Epic"),
	EQ_Cinematic = 4 UMETA(DisplayName = "Cinematic"),
	EQ_MAX = 5 UMETA(DisplayName = "DefaultMAX"),
};

UCLASS()
class VRMINIGAME_API USettingsMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	class UComboBoxString* GraphicsOptions;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	class USlider* MusicSlider;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	class USlider* EffectsSlider;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	class USlider* VoipSlider;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	class UButton* BackButton;

private:
	void FillQualityComboBoxAndSetValue(UComboBoxString* ComboBox, int32 CurrentValue);

	uint8 GetEnumIndexByName(FString Name);

	UFUNCTION()
	void GraphicsOnSelectionChange(FString SelectedItem, ESelectInfo::Type SelectionType);

};
