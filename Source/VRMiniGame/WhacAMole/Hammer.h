#pragma once

#include "CoreMinimal.h"
#include "Grippables/GrippableStaticMeshActor.h"
#include "Grippables/HandSocketComponent.h"
#include "VRPlayerController.h"
#include "VRCharacter.h"
#include "Hammer.generated.h"

UCLASS()
class VRMINIGAME_API AHammer : public AGrippableStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	AHammer(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;
	virtual void OnRep_Owner() override;

	UFUNCTION(BlueprintCallable)
	virtual void Dropped();

protected:
	virtual void BeginPlay() override;
	class UGrippableStaticMeshComponent* GrippableStaticMeshComponent;
	bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const;
	bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const;
	bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const;

	/*
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USplineComponent* GripLine;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USceneComponent* WepOrientation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UHandSocketComponent* GripRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHandSocketComponent* ReverseGripRotation;*/

	UPROPERTY()
	class AVRCharacter* OwnerCharacter;
	UPROPERTY()
	class AVRPlayerController* OwnerController;
};
