// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "Actor/TowerProjectileBase.h"
#include "TowerLinearProjectile.generated.h"

/**
 * @ingroup Tower
 */
UCLASS()
class TOWER_API ATowerLinearProjectile : public ATowerProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATowerLinearProjectile();
	virtual void Tick(float DeltaSeconds) override;

	virtual void InitProjectileParams(float Damage, float InitSpeed, float InMaxSpeed, TScriptInterface<ITowerEnemyInterface> InTargetEnemy) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void LaunchAtTarget(FVector StartLocation, FVector EndLocation, float Damage, bool bHasArch = false, float ArcHeight = 500.f) override;
	virtual void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	float HomingStrength = 1.f;
};
