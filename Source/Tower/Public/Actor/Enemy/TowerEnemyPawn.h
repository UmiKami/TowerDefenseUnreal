// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interaction/TowerEnemyInterface.h"
#include "TowerEnemyPawn.generated.h"

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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> PawnSkeletalMesh;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> CapsuleCollision;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPawnMovementComponent> PawnMovementComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Navigation")
	TObjectPtr<ATowerEnemyPathActor> PathToFollow;
	
public:
	virtual void Tick(float DeltaSeconds) override;
	
private:
	bool IsMoving = false;
	
	UPROPERTY()
	TObjectPtr<AAIController> PawnAIController = nullptr;
	
	float CurrentSplineProgress = 0.f;
	
	void MoveActorAlongSpline();
};
