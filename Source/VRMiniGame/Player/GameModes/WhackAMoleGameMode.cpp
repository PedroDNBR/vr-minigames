#include "WhackAMoleGameMode.h"

void AWhackAMoleGameMode::HandleSeamlessTravelPlayer(AController*& C)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			"Mudou de cena"
		);
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			C->GetName()
		);
	}
}
