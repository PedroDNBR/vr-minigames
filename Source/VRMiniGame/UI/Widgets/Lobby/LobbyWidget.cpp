#include "LobbyWidget.h"
#include "VRMiniGame/Player/GameState/MiniGameGameState.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool ULobbyWidget::Initialize()
{
	if (!Super::Initialize()) {
		return false;
	}

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &ThisClass::StartGame);
	}

	return true;
}

void ULobbyWidget::StartGame()
{
	AMiniGameGameState* BlasterGameState = Cast<AMiniGameGameState>(UGameplayStatics::GetGameState(this));

	if (BlasterGameState == nullptr || !BlasterGameState) return;

	BlasterGameState->StartRandomMiniGame();

}
