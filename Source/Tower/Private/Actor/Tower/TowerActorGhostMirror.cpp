// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Actor/Tower/TowerActorGhostMirror.h"


ATowerActorGhostMirror::ATowerActorGhostMirror()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("TowerMesh");
	
	Mesh->SetupAttachment(RootComponent);
}
