

#pragma once

#include "CoreMinimal.h"
#include "TankPawn.h"
#include "MapLoader.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "TankFactory.generated.h"

UCLASS()
class TANKOGEDDON_API ATankFactory : public AActor, public IDamageTaker
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BuildingMesh;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent * TankSpawnPoint;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent * HitCollider;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UHealthComponent * HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn tanks params")
	TSubclassOf<ATankPawn> SpawnTankClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn tanks params")
	float SpawnTankRate = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn tanks params")
	TArray<ATargetPoint*> TankWayPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn tanks params")
	AMapLoader* LinkedMapLoader;

public:	

	ATankFactory();
	
	UFUNCTION()
	void TakeDamage(FDamageData DamageData);

protected:
	
	virtual void BeginPlay() override;
	
	void SpawnNewTank();
	
	UFUNCTION()
	void Die();
	
	UFUNCTION()
	void DamageTaked(float DamageValue);
	
};
