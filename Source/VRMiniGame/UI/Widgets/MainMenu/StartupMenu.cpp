#include "StartupMenu.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

bool UStartupMenu::Initialize()
{
	if (!Super::Initialize()) {
		return false;
	}

	if (Quit)
	{
		Quit->OnClicked.AddDynamic(this, &ThisClass::QuitGame);
	}

	return true;
}

void UStartupMenu::QuitGame()
{
	UWorld* World = GetWorld();

	TEnumAsByte<EQuitPreference::Type> QuitPreference = EQuitPreference::Quit;
	
	UKismetSystemLibrary::QuitGame(
		World,
		World->GetFirstPlayerController(),
		QuitPreference,
		false
	);
}
