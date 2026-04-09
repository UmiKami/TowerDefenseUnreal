// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Actor/Projectile/TowerArchedProjectile.h"


// Sets default values
ATowerArchedProjectile::ATowerArchedProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATowerArchedProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerArchedProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

