// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Actor/Enemy/TowerEnemyPathActor.h"

#include "Components/SplineComponent.h"


ATowerEnemyPathActor::ATowerEnemyPathActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SplinePath = CreateDefaultSubobject<USplineComponent>("SplinePath");
	
	SetRootComponent(SplinePath);
}
