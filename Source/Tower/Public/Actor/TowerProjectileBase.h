// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerProjectileBase.generated.h"

class ITowerEnemyInterface;
class UBoxComponent;
class UProjectileMovementComponent;

/**
 * @brief Determines behavior of each projectile.
 * 
 * @ingroup Tower
 */
UCLASS()
class TOWER_API ATowerProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	ATowerProjectileBase();
	
	
	UFUNCTION()
	virtual void InitProjectileParams(float InDamage, float InitSpeed, float InMaxSpeed, TScriptInterface<ITowerEnemyInterface> InTargetEnemy);
	/**
	 * @brief Validates parameters and checks if projectile can be launched, if it can be launch then it we will call @see LaunchAtTarget() method.
	 * @param StartLocation Where the projectile spawns.
	 * @param EndLocation   Where it should land.
	 * @param InDamage		Amount of Damage that it should do on hit
	 * @param ArcHeight     How high the arc peaks above the midpoint. 
	 *                      Higher = floatier, lower = flatter.
	 */
	UFUNCTION()
	void TryLaunchAtTarget(FVector StartLocation, FVector EndLocation, float InDamage, bool bHasArch = false, float ArcHeight = 500.f);
protected:
	virtual void BeginPlay() override;
	

	
	/**
	 * @brief Launches the projectile toward a target with the option of using ballistic arc.
	 * @param StartLocation Where the projectile spawns.
	 * @param EndLocation   Where it should land.
	 * @param InDamage		Amount of Damage that it should do on hit
	 * @param InitSpeed		Initial velocity of projectile on Spawn
	 * @param InMaxSpeed	Maximum possible velocity.
	 * @param ArcHeight     How high the arc peaks above the midpoint. 
	 *                      Higher = floatier, lower = flatter.
	 */
	UFUNCTION()
	virtual void LaunchAtTarget(FVector StartLocation, FVector EndLocation, float InDamage, bool bHasArch = false, float ArcHeight = 500.f);
	
	/**
	 * @brief Called when the projectile hits something.
	 * @param OverlappedComponent  The component on this projectile that was hit.
	 * @param OtherActor    The actor that was hit.
	 * @param OtherComp     The component on the other actor that was hit.
	 * @param NormalImpulse The impulse applied at the hit point.
	 * @param bFromSweep
	 * @param Hit           Detailed hit result data.
	 */
	UFUNCTION()
	virtual void OnHit(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult
	);
	
	UPROPERTY()
	TScriptInterface<ITowerEnemyInterface> TargetEnemy;
	

	
	/** @brief Mesh of the projectile (sphere for cannonball, capsule for arrow). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	
	/** @brief Collision capsule for hit detection. */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> BoxCollision;
	
	/** @brief Acts as root component and allows to rotate collision component as desired. */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> SceneComponent;
	
	/** @brief Damage dealt on impact. */
	UPROPERTY(EditDefaultsOnly)
	float Damage = 25.f;
};
