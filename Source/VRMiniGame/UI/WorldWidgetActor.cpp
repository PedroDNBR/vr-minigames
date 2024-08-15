#include "WorldWidgetActor.h"
#include "Components/WidgetComponent.h"

AWorldWidgetActor::AWorldWidgetActor()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(Root);

	PointsWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PointsWidget"));
	PointsWidget->SetupAttachment(RootComponent);
	PointsWidget->SetIsReplicated(true);
}