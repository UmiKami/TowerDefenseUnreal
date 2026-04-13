// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Actor/TowerActorBase.h"

#include "Actor/Projectile/TowerLinearProjectile.h"
#include "Data/TowerClassInfo.h"

ATowerActorBase::ATowerActorBase()
{
	PrimaryActorTick.bCanEverTick = false;;
	DisableComponentsSimulatePhysics();
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	SetRootComponent(BoxCollider);
	
	TowerRangeDiskMesh = CreateDefaultSubobject<UStaticMeshComponent>("TowerRangeDisk");
	TowerRangeDiskMesh->SetupAttachment(RootComponent);
	
	TowerMesh = CreateDefaultSubobject<USkeletalMeshComponent>("TowerSkeletalMesh");
	TowerMesh->SetupAttachment(RootComponent);
}

void ATowerActorBase::SetTowerClass(const ETowerClass& InTowerClass)
{
	TowerClass = InTowerClass;
}

void ATowerActorBase::BeginPlay()
{
	Super::BeginPlay();

	checkf(TowerClassInfo, TEXT("TowerClassInfo DataAsset MUST be set in tower actor BEFORE spawn."))

	TowerRangeDiskMesh->SetVisibility(false);

	TowerClasDefaultInfo = TowerClassInfo->TowerClassInformation.Find(TowerClass);
	USkeletalMesh* SkeletalMeshComponent = *TowerClasDefaultInfo->SkeletalMeshComponentPerLevel.Find(Level);

	TowerMesh->SetSkeletalMesh(SkeletalMeshComponent);
	Damage = TowerClasDefaultInfo->DamageCurve.GetCurve("DamageCurve Not Found")->Eval(Level);
	FireRate = TowerClasDefaultInfo->FireRateCurve.GetCurve("FireRateCurve Not Found")->Eval(Level);

	TowerRangeDiskMesh->SetRelativeScale3D({TowerAttackRange, TowerAttackRange, .2f});
	
	TowerRangeDiskMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnActorOverlap);
	
}

void ATowerActorBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UTowerEnemyInterface>()) return;
	
	// TODO Spawn and launch projectile towards actor location

	FVector StartLocation = TowerMesh->GetSocketLocation("ArrowFirePoint");

	FVector EndLocation = OtherActor->GetTargetLocation();
	FVector Direction = (EndLocation - StartLocation).GetSafeNormal();
	
	FRotator SpawnRotation = Direction.Rotation();
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = GetInstigator();
	
	if (TowerClasDefaultInfo->ProjectileClass)
	{
		ATowerProjectileBase* Projectile = GetWorld()->SpawnActor<ATowerLinearProjectile>(TowerClasDefaultInfo->ProjectileClass, StartLocation, SpawnRotation, SpawnParameters);
		
		Projectile->TryLaunchAtTarget(StartLocation, EndLocation, Damage, 2000.f, 2000.f);
	}
}

void ATowerActorBase::ActorSelected()
{
	TowerRangeDiskMesh->SetVisibility(true);
}

void ATowerActorBase::ActorDeselected()
{
	TowerRangeDiskMesh->SetVisibility(false);
}
