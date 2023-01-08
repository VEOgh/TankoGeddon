

#pragma once


#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Cannon.h"
#include "Turret.generated.h"

class UStaticMeshComponent;
class ACannon;



UCLASS()
class TANKOGEDDON_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurret();

protected:
	virtual void BeginPlay() override;

	void Targeting();
	void Destroyed();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();

	void SetupCannon();
	
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* HitCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<ACannon> CannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* CannonSetupPoint;
	
	UPROPERTY()
	ACannon* Cannon;

	UPROPERTY()
	APawn* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting params")
	float TargetingRange = 1000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting params")
	float TargetingSpeed = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting params")
	float TargetingRate = 0.005f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting params")
	float Accurency = 10.0f;

	const FString BodyMeshPath = "/Script/Engine.StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'";
	const FString TurretMeshPath = "/Script/Engine.StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'";

	 
	
};
