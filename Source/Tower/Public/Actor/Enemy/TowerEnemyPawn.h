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
class ATowerEnemyPawn;

/**
 * @brief Delegate fired when pawn dies.
 * @param EnemyPawn Pointer to the pawn that died.
 * @ingroup Tower
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyDiedSignature, ATowerEnemyPawn*, EnemyPawn);

/**
 * @brief Player's enemy pawn. Capable of killing the player 🤷‍♂️
 *
 * @ingroup Tower
 */
UCLASS()
class TOWER_API ATowerEnemyPawn : public APawn, public ITowerEnemyInterface
{
	GENERATED_BODY()

public:
	/**
	 * @brief Creates the enemy pawn and its default components.
	 */
	ATowerEnemyPawn();

	/** 
	 * @brief Returns the current location of the actor.
	 * @return FVector of current location of actor.
	 */
	virtual FVector GetCurrentLocation() const override;

	/**
	 * @brief Signature fired when pawn dies.
	 */
	UPROPERTY(BlueprintAssignable)
	FEnemyDiedSignature OnDeath;

	virtual bool IsValidPtr() const override;

	UFUNCTION(BlueprintPure)
	float GetKillReward() const;
	
protected:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/**
	 * @brief Initializes runtime state when the pawn enters play.
	 */
	virtual void BeginPlay() override;


	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	/**
	 * @brief Current health available to the pawn.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	float Health;

	/**
	 * @brief Maximum health value the pawn can have.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, Category="Stats")
	FCurveTableRowHandle MaxHealthCurve;

	/**
	 * @brief Skeletal mesh used to render the pawn.
	 */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> PawnSkeletalMesh;

	/**
	 * @brief Capsule collision used for overlap and hit detection.
	 */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> CapsuleCollision;

	/**
	 * @brief Movement component that drives pawn translation.
	 */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UFloatingPawnMovement> PawnMovementComponent;

	/**
	 * @brief Path actor whose spline this pawn follows.
	 */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ATowerEnemyPathActor> PathToFollow;

	UPROPERTY(EditDefaultsOnly, Category="Stats")
	FCurveTableRowHandle MovementSpeedCurve;
	/**
	 * @brief Movement speed used while traversing the spline.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MovementSpeed = 300.f;

	UPROPERTY(EditDefaultsOnly, Category="Stats")
	FCurveTableRowHandle DamageCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float Damage = 10.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Loot")
	float GoldRewardOnKill = 5.f;

public:
	virtual void Tick(float DeltaSeconds) override;

private:
	/**
	 * @brief Indicates whether the pawn should currently advance along its path.
	 */
	bool IsMoving = false;

	/**
	 * @brief AI controller assigned to this pawn.
	 */
	UPROPERTY()
	TObjectPtr<AAIController> PawnAIController = nullptr;

	/**
	 * @brief Distance already travelled along the active spline path.
	 */
	float CurrentDistanceTravelled = 0.f;

	/**
	 * @brief Advances the pawn along its assigned spline path.
	 */
	void MoveActorAlongSpline();

	void SetInitialProperties();
};
