

#pragma once

#include "Cannon.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoBox.generated.h"

UCLASS()
class TANKOGEDDON_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAmmoBox();

protected:

	UFUNCTION()
	void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* AmmoMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<class ACannon> CannonClass;
};
