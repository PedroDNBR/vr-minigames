// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grippables/GrippableStaticMeshActor.h"
#include "DestructibleGrippableStaticMesh.generated.h"

/**
 * 
 */
UCLASS()
class VRMINIGAME_API ADestructibleGrippableStaticMesh : public AGrippableStaticMeshActor
{
	GENERATED_BODY()

public:
	ADestructibleGrippableStaticMesh(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;


protected:
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const;
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const;
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProceduralMeshComponent* ProceduralMesh;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
