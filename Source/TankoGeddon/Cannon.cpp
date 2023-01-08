// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"


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
	if(!IsReadyToFire())
	{
		return;
	}
	bReadyToFire = false;

	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire projectile")));
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		if (projectile)
		{
			projectile->Start();
		}
		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire trace")));
		FHitResult hitResult;
		FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("Fire Trace")), true, this);;
		traceParams.bTraceComplex = true;
		traceParams.bReturnPhysicalMaterial = false;

		FVector Start = ProjectileSpawnPoint->GetComponentLocation();
		FVector End = ProjectileSpawnPoint->GetForwardVector() * FireRange + Start;

		if(GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECollisionChannel::ECC_EngineTraceChannel1, traceParams))
		{
			DrawDebugLine(GetWorld(), Start, hitResult.Location, FColor::Red, false, 1.0f, 0, 5);
			if (hitResult.GetActor())
			{
				UE_LOG(LogTemp, Warning, TEXT("trace overlap : %s"), *hitResult.GetActor()->GetName());
				hitResult.GetActor()->Destroy();
			}
			else
			{
				DrawDebugLine(GetWorld(), Start, End, FColor::Purple, false, 1.0f, 0, 5.0f);
			}
				
		}
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);
	
}

void ACannon::Reload()
{
		bReadyToFire = true;
}

bool ACannon::IsReadyToFire()
{
	return bReadyToFire;	
}


