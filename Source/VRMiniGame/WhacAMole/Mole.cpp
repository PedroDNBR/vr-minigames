#include "Mole.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "VRCharacter.h"
#include "VRMiniGame/Player/MiniGamePlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Hammer.h"

AMole::AMole()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetIsReplicated(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetNotifyRigidBodyCollision(true);
	Mesh->BodyInstance.bNotifyRigidBodyCollision = true;
}

void AMole::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority()) return;

	StartHeight = UKismetMathLibrary::Conv_DoubleToInt64(Mesh->GetRelativeLocation().Z);

	SetState(EMoleState::EMS_Idle);
}

void AMole::Ascend()
{
	if (!HasAuthority()) return;
	SetState(EMoleState::EMS_Ascending);
}

void AMole::Ascended()
{
	if (!HasAuthority()) return;
	SetState(EMoleState::EMS_Ascended);
	Mesh->OnComponentHit.AddDynamic(this, &AMole::OnHit);
	GetWorld()->GetTimerManager().SetTimer(
		AscendTimer,
		this,
		&AMole::Descend,
		UKismetMathLibrary::RandomFloatInRange(0.8f, 2.5f)
	);
}

void AMole::Descend()
{
	if (!HasAuthority()) return;
	SetState(EMoleState::EMS_Descending);
	Mesh->OnComponentHit.RemoveAll(this);
}

void AMole::Descended()
{
	if (!HasAuthority()) return;
	GetWorld()->GetTimerManager().SetTimer(
		AscendTimer,
		this,
		&AMole::Ascend,
		UKismetMathLibrary::RandomFloatInRange(1.5f, 5.5f)
	);
	SetState(EMoleState::EMS_Idle);
}

void AMole::Hitted()
{
	if (!HasAuthority()) return;
	Mesh->OnComponentHit.RemoveAll(this);
	Descend();
}

void AMole::AscendMoleMovement(float DeltaTime)
{
	if (!HasAuthority()) return;
	if ((float)Mesh->GetRelativeLocation().Z < AscendHeight)
	{
		Mesh->SetRelativeLocation(FVector(0, 0, Mesh->GetRelativeLocation().Z + DeltaTime * Speed));
	}
	if ((float)Mesh->GetRelativeLocation().Z >= AscendHeight)
	{
		Mesh->SetRelativeLocation(FVector(0, 0, AscendHeight));
		Ascended();
	}
}

void AMole::DescendMoleMovement(float DeltaTime)
{
	if (!HasAuthority()) return;
	if ((float)Mesh->GetRelativeLocation().Z > StartHeight)
	{
		Mesh->SetRelativeLocation(FVector(0, 0, Mesh->GetRelativeLocation().Z - DeltaTime * Speed));
	}
	if ((float)Mesh->GetRelativeLocation().Z <= StartHeight)
	{
		Mesh->SetRelativeLocation(FVector(0, 0, StartHeight));
		Descended();
	}
}

void AMole::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!HasAuthority()) return;
	if (OtherActor)
	{
		AHammer* Hammer = Cast<AHammer>(OtherActor);
		if (Hammer && (float) Hammer->GetVelocity().Length() > 200.f)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, "Bateu forte");
			}
			AVRCharacter* Character = Cast<AVRCharacter>(Hammer->GetOwner());
			if (Character)
			{
				AMiniGamePlayerState* PlayerState = Cast<AMiniGamePlayerState>(Character->GetPlayerState());
				if (PlayerState)
				{
					PlayerState->AddToScore(1.f);
				}
			}
			Hitted();
		}
	}
}

void AMole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HasAuthority()) return;

	switch (State)
	{
	case EMoleState::EMS_Idle:
		break;
	case EMoleState::EMS_Ascended:
		
		break;
	case EMoleState::EMS_Ascending:
		AscendMoleMovement(DeltaTime);
		break;
	case EMoleState::EMS_Descending:
		DescendMoleMovement(DeltaTime);
		break;
	case EMoleState::EMS_Descended:
		break;
	case EMoleState::EMS_Hitted:
		break;
	case EMoleState::EMS_MAX:
		break;
	default:
		break;
	}
}

void AMole::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMole, State);
}

void AMole::StartMole()
{
	Descended();
}
