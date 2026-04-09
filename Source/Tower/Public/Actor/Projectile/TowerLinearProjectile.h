// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "Actor/TowerProjectileBase.h"
#include "TowerLinearProjectile.generated.h"

UCLASS()
class TOWER_API ATowerLinearProjectile : public ATowerProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATowerLinearProjectile(); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void LaunchAtTarget(FVector StartLocation, FVector EndLocation, float Damage, float InitSpeed, float InMaxSpeed, bool bHasArch = false, float ArcHeight = 500.f) override;
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

};
