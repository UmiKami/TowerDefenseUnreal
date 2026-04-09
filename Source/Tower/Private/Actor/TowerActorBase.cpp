// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Actor/TowerActorBase.h"

#include "Data/TowerClassInfo.h"

ATowerActorBase::ATowerActorBase()
{
	PrimaryActorTick.bCanEverTick = false;;
	DisableComponentsSimulatePhysics();
	
	TowerRangeDiskMesh = CreateDefaultSubobject<UStaticMeshComponent>("TowerRangeDisk");
	
	SetRootComponent(TowerRangeDiskMesh);
	
	TowerMesh = CreateDefaultSubobject<USkeletalMeshComponent>("TowerSkeletalMesh");
}

void ATowerActorBase::SetTowerClass(const ETowerClass& InTowerClass)
{
	TowerClass = InTowerClass;
}

void ATowerActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	checkf(TowerClassInfo, TEXT("TowerClassInfo DataAsset MUST be set in tower actor BEFORE spawn."))
	
	TowerClasDefaultInfo = TowerClassInfo->TowerClassInformation.Find(TowerClass);
	USkeletalMesh* SkeletalMeshComponent = *TowerClasDefaultInfo->SkeletalMeshComponentPerLevel.Find(Level);
	
	TowerMesh->SetSkeletalMesh(SkeletalMeshComponent);
	Damage = TowerClasDefaultInfo->DamageCurve.Eval(Level);
	
	TowerRangeDiskMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnActorOverlap);
}

void ATowerActorBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UTowerEnemyInterface>()) return;
	
	// TODO Spawn and launch projectile towards actor location
}
