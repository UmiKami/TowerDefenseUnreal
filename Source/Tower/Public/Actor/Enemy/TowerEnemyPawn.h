// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interaction/TowerEnemyInterface.h"
#include "TowerEnemyPawn.generated.h"

class UFloatingPawnMovement;
class AAIController;
class UCapsuleComponent;
class ATowerEnemyPathActor;
class USplineComponent;

/**
 * @ingroup Tower
 */
UCLASS()
class TOWER_API ATowerEnemyPawn : public APawn, public ITowerEnemyInterface
{
	GENERATED_BODY()

public:
	ATowerEnemyPawn();
	
	virtual FVector GetCurrentLocation() const override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> PawnSkeletalMesh;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> CapsuleCollision;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UFloatingPawnMovement> PawnMovementComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ATowerEnemyPathActor> PathToFollow;
	
	UPROPERTY(EditAnywhere, Category="Movement")
	float MovementSpeed = 300.f;
	
public:
	virtual void Tick(float DeltaSeconds) override;
	
private:
	bool IsMoving = false;
	
	UPROPERTY()
	TObjectPtr<AAIController> PawnAIController = nullptr;
	
	float CurrentDistanceTravelled = 0.f;
	
	void MoveActorAlongSpline();
};
