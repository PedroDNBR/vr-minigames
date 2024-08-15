// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleGrippableStaticMesh.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

ADestructibleGrippableStaticMesh::ADestructibleGrippableStaticMesh(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UOptionalRepStaticMeshComponent>(TEXT("StaticMeshComponent0")))
{
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
}

void ADestructibleGrippableStaticMesh::BeginPlay()
{
	ProceduralMesh->OnComponentHit.AddDynamic(
		this, 
		&ADestructibleGrippableStaticMesh::OnHit
	);
}

bool ADestructibleGrippableStaticMesh::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return false;
}

bool ADestructibleGrippableStaticMesh::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return false;
}

bool ADestructibleGrippableStaticMesh::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return false;
}

void ADestructibleGrippableStaticMesh::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AGrippableStaticMeshActor* Grippable = Cast<AGrippableStaticMeshActor>(OtherActor);
	if (Grippable && ProceduralMesh)
	{
		UProceduralMeshComponent* Otherhalf;
		UKismetProceduralMeshLibrary::SliceProceduralMesh(
			ProceduralMesh,
			Hit.Location,
			Grippable->GetActorLocation().UpVector,
			true,
			Otherhalf,
			EProcMeshSliceCapOption::CreateNewSectionForCap,
			ProceduralMesh->GetMaterial(0)
		);
		OtherActor->AddInstanceComponent(Otherhalf);
		Otherhalf->SetSimulatePhysics(true);

		// OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	}
}
