// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Actor/Tower/TowerSnapArea.h"

ATowerSnapArea::ATowerSnapArea()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SnapAreaRecognitionRangeMesh = CreateDefaultSubobject<UStaticMeshComponent>("HoverArea");
	
	SetRootComponent(SnapAreaRecognitionRangeMesh);
}
