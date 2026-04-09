// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerProjectileBase.generated.h"

class UCapsuleComponent;
class USphereComponent;
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

protected:
	virtual void BeginPlay() override;
	
	/**
	 * @brief Validates parameters and checks if projectile can be launch, if it can be launch then it we will call @see LaunchAtTarget() method.
	 * @param StartLocation Where the projectile spawns.
	 * @param EndLocation   Where it should land.
	 * @param Damage		Amount of Damage that it should do on hit
	 * @param InitSpeed		Initial velocity of projectile on Spawn
	 * @param InMaxSpeed	Maximum possible velocity.
	 * @param ArcHeight     How high the arc peaks above the midpoint. 
	 *                      Higher = floatier, lower = flatter.
	 */
	UFUNCTION()
	void TryLaunchAtTarget(FVector StartLocation, FVector EndLocation, float Damage, float InitSpeed, float InMaxSpeed, bool bHasArch = false, float ArcHeight = 500.f);
	
	/**
	 * @brief Launches the projectile toward a target with the option of using ballistic arc.
	 * @param StartLocation Where the projectile spawns.
	 * @param EndLocation   Where it should land.
	 * @param Damage		Amount of Damage that it should do on hit
	 * @param InitSpeed		Initial velocity of projectile on Spawn
	 * @param InMaxSpeed	Maximum possible velocity.
	 * @param ArcHeight     How high the arc peaks above the midpoint. 
	 *                      Higher = floatier, lower = flatter.
	 */
	UFUNCTION()
	virtual void LaunchAtTarget(FVector StartLocation, FVector EndLocation, float Damage, float InitSpeed, float InMaxSpeed, bool bHasArch = false, float ArcHeight = 500.f);
	
	/**
	 * @brief Called when the projectile hits something.
	 * @param HitComponent  The component on this projectile that was hit.
	 * @param OtherActor    The actor that was hit.
	 * @param OtherComp     The component on the other actor that was hit.
	 * @param NormalImpulse The impulse applied at the hit point.
	 * @param Hit           Detailed hit result data.
	 */
	UFUNCTION()
	virtual void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	
	/** @brief The movement component driving this projectile. */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	/** @brief Mesh of the projectile (sphere for cannonball, capsule for arrow). */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	
	/** @brief Collision sphere for hit detection. */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> SphereCollision;
	
	/** @brief Damage dealt on impact. */
	UPROPERTY(EditDefaultsOnly)
	float Damage = 25.f;
};
