#include "WhackAMoleGameMode.h"
#include "VRMiniGame/WhacAMole/Mole.h"
#include "Kismet/GameplayStatics.h"

void AWhackAMoleGameMode::StartMiniGameMatch()
{
	Super::StartMiniGameMatch();
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMole::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		AMole* Mole = Cast<AMole>(Actor);
		if (Mole)
		{
			Mole->StartMole();
		}
	}
}
