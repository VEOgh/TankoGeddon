// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"


ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;
	
	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = sceneComp;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(sceneComp);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);

}


void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
	
}

void ACannon::Fire()
{
	if(FireAmmo==0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2,FColor::Red, "Out of Ammo");
	}

	if(!IsReadyToFire())
	{
		return;
	}
	bReadyToFire = false;
	
	if(FireAmmo!=0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2,FColor::Green, FString::Printf(TEXT("Bah Bah %f"), FireAmmo));
		FireAmmo--;
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);
}

void ACannon::SpecialFire()

{
	if(!IsReadyToFire())
	{
		return;
	}
	bReadyToFire = false;
	
	
	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Fire projectile")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Fire trace")));
	}
	
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 0.1 / FireRate, false);
}



/*void ACannon::Fire()
{
	if(!IsReadyToFire())
	{
		return;
	}
	bReadyToFire = false;

	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire projectile")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire trace")));
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);
	
}*/

void ACannon::Reload()
{
		bReadyToFire = true;
}

bool ACannon::IsReadyToFire()
{
	return bReadyToFire;	
}


