// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "GameStructs.h"
#include "Projectile.h"
#include "Camera/CameraShakeBase.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ForceFeedbackEffect.h"
#include "Particles/ParticleSystemComponent.h"
#include "Cannon.generated.h"


UCLASS()
class TANKOGEDDON_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:
	ACannon();

	void Fire();
	void Reload();
	bool IsReadyToFire();

	FTimerHandle ReloadTimer;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	class UStaticMeshComponent* CannonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	TSubclassOf <class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	ECannonType CannonType = ECannonType::FireProjectile;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UParticleSystemComponent* ShootEffect;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UAudioComponent* AudioEffect;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire params")
	float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire params")
	float FireRange = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire params")
	float FireDamage = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire params")
	float FireAmmo = 9.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UForceFeedbackEffect * ShootForceEffect;

	//TSubclassOf<UCameraShake> ShootShake;
	UPROPERTY(EditAnywhere)
TSubclassOf<UCameraShakeBase> ShootShake;
	

private:
	bool bReadyToFire = false;

};