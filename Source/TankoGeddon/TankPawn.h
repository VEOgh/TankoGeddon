

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "DamageTaker.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
UCLASS()
class TANKOGEDDON_API ATankPawn : public APawn, public IDamageTaker
{
	GENERATED_BODY()

public:
	ATankPawn();

	virtual void Tick(float DeltaTime) override;

	void MoveForward(float value);
	void MoveRight(float value);
	void RotateRight(float value);

	void SetupCannon(TSubclassOf<ACannon> newCannon);
	void Fire();

	FVector GetEyesPosition();

	UFUNCTION()
	TArray<FVector> GetPatrollingPoints() {return PatrollingPoints;};
	
	UFUNCTION()
	float GetMovementAccurency() {return MovementAccurency; };
	
	UFUNCTION(BlueprintCallable)
	class UHealthComponent* GetHealthComponent() const { return HealthComponent; }

	UFUNCTION()
	virtual void TakeDamage(FDamageData DamageData) override;

	UFUNCTION()
	FVector GetTurretForwardVector();
	
	UFUNCTION()
	void RotateTurretTo(FVector TargetPosition);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* TurretMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	class UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	class UHealthComponent* HealthComponent;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cannon")
	TSubclassOf<ACannon> CannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cannon")
	class UArrowComponent* CannonSetupPoint;

	UPROPERTY()
	ACannon* Cannon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MovementSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float RotationSpeed = 100.0f;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points" , Meta = (MakeEditWidget = true))
	TArray<FVector> PatrollingPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurency")
	float MovementAccurency = 50;

	void Die();
	void DamageTaked(float Value);
private:
	class ATankController* TankController;
	
	float ForwardMoveAxisValue = 0.0f;
	float RightMoveAxisValue = 0.0f;
	float CurrentRightAxisValue = 0.0f;
	float RotateRightAxisValue = 0.0f;
	float RotateInterpolationKey = 0.1f;
	float TurretInterpolationKey = 0.5f;
	

};