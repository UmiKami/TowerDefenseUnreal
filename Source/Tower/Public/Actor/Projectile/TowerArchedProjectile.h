// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "Actor/TowerProjectileBase.h"
#include "TowerArchedProjectile.generated.h"

UCLASS()
class TOWER_API ATowerArchedProjectile : public ATowerProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATowerArchedProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
