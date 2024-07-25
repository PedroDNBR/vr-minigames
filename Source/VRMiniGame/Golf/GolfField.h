#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GolfField.generated.h"

UCLASS()
class VRMINIGAME_API AGolfField : public AActor
{
	GENERATED_BODY()
	
public:	
	AGolfField();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AGolfBall> GolfBallClass;

private:	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* PointsCollider;

	UPROPERTY(EditAnywhere)
	UBoxComponent* SpawnerCollider;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SpawnGolfBall();

};
