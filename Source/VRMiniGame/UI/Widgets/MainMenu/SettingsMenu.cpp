#include "SettingsMenu.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"

bool USettingsMenu::Initialize()
{
	if (!Super::Initialize()) {
		return false;
	}

	GraphicsOptions->OnSelectionChanged.AddDynamic(this, &USettingsMenu::GraphicsOnSelectionChange);

	UGameUserSettings* UserSettings = Cast<UGameUserSettings >(GEngine->GetGameUserSettings());

	if (GraphicsOptions)
	{
		int32 CurrentQualityLevelIndex = UserSettings->GetOverallScalabilityLevel();

		if (CurrentQualityLevelIndex < 0)
		{
			UserSettings->SetOverallScalabilityLevel(0);
			CurrentQualityLevelIndex = UserSettings->GetOverallScalabilityLevel();
		}
		FillQualityComboBoxAndSetValue(GraphicsOptions, CurrentQualityLevelIndex);
	}

	UserSettings->ApplySettings(true);
	return true;
}

void USettingsMenu::FillQualityComboBoxAndSetValue(UComboBoxString* ComboBox, int32 CurrentValue)
{
	for (uint8 i = 0; i < EQuality::EQ_MAX; i++)
	{
		FText QualityLevels;
		UEnum::GetDisplayValueAsText(EQuality(i), QualityLevels);
		ComboBox->AddOption(QualityLevels.ToString());
	}

	FText CurrentQualityLevel;

	UEnum::GetDisplayValueAsText(EQuality(CurrentValue), CurrentQualityLevel);
	ComboBox->SetSelectedOption(CurrentQualityLevel.ToString());
}

void USettingsMenu::GraphicsOnSelectionChange(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	UGameUserSettings* UserSettings = Cast<UGameUserSettings >(GEngine->GetGameUserSettings());

	int8 Index = GetEnumIndexByName(SelectedItem);

	if (Index > -1)
	{
		UserSettings->SetOverallScalabilityLevel(Index);
	}

	UserSettings->ApplySettings(true);
}

uint8 USettingsMenu::GetEnumIndexByName(FString Name)
{
	for (uint8 i = 0; i < EQuality::EQ_MAX; i++)
	{
		FText QualityLevels;
		UEnum::GetDisplayValueAsText(EQuality(i), QualityLevels);
		if (QualityLevels.ToString() == Name) return i;
	}

	return -1;
}