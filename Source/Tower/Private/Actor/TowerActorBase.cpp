// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Actor/TowerActorBase.h"

#include "Actor/Enemy/TowerEnemyPawn.h"
#include "Actor/Projectile/TowerLinearProjectile.h"
#include "Components/BoxComponent.h"
#include "Data/TowerClassInfo.h"
#include "Kismet/KismetSystemLibrary.h"

ATowerActorBase::ATowerActorBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DisableComponentsSimulatePhysics();

	BoxCollider = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	SetRootComponent(BoxCollider);

	TowerRangeDiskMesh = CreateDefaultSubobject<UStaticMeshComponent>("TowerRangeDisk");
	TowerRangeDiskMesh->SetupAttachment(RootComponent);

	TowerMesh = CreateDefaultSubobject<USkeletalMeshComponent>("TowerSkeletalMesh");
	TowerMesh->SetupAttachment(RootComponent);
}

void ATowerActorBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Targets.IsEmpty())
	{
		GetWorldTimerManager().ClearTimer(FireRateTimer);
		SetActorTickEnabled(false);
	}
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
	TowerRangeDiskMesh->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnActorOverlapEnd);
}

void ATowerActorBase::Fire()
{
	if (Targets.IsEmpty()) return;

	TObjectPtr<ATowerEnemyPawn> EnemyPawn = Targets[0];
	
	FVector EndLocation = EnemyPawn->GetTargetLocation();
	FVector StartLocation;

	const float FromLeftWeaponPort = FVector::Dist(TowerMesh->GetSocketLocation("ArrowFirePoint_Left"), EndLocation);
	const float FromRightWeaponPort = FVector::Dist(TowerMesh->GetSocketLocation("ArrowFirePoint_Right"), EndLocation);
	const float FromFrontWeaponPort = FVector::Dist(TowerMesh->GetSocketLocation("ArrowFirePoint_Front"), EndLocation);
	const float FromBackWeaponPort = FVector::Dist(TowerMesh->GetSocketLocation("ArrowFirePoint_Back"), EndLocation);

	const float Min = FMath::Min(FromLeftWeaponPort, FromRightWeaponPort, FromFrontWeaponPort, FromBackWeaponPort);

	if (Min == FromLeftWeaponPort) StartLocation = TowerMesh->GetSocketLocation("ArrowFirePoint_Left");
	if (Min == FromRightWeaponPort) StartLocation = TowerMesh->GetSocketLocation("ArrowFirePoint_Right");
	if (Min == FromFrontWeaponPort) StartLocation = TowerMesh->GetSocketLocation("ArrowFirePoint_Front");
	if (Min == FromBackWeaponPort) StartLocation = TowerMesh->GetSocketLocation("ArrowFirePoint_Back");

	FVector Direction = (EndLocation - StartLocation).GetSafeNormal();
	FRotator SpawnRotation = Direction.Rotation();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = GetInstigator();

	FTransform ProjectileTransform;
	ProjectileTransform.SetTranslation(StartLocation);
	ProjectileTransform.SetRotation(SpawnRotation.Quaternion());
	
	ATowerLinearProjectile* Projectile = GetWorld()->SpawnActorDeferred<ATowerLinearProjectile>(TowerClasDefaultInfo->ProjectileClass, ProjectileTransform, this, GetInstigator());

	TScriptInterface<ITowerEnemyInterface> EnemyTarget = EnemyPawn;

	Projectile->InitProjectileParams(Damage, 2000.f, 2000.f, EnemyTarget);

	Projectile->FinishSpawning(ProjectileTransform);

	Projectile->TryLaunchAtTarget(StartLocation, EndLocation, Damage, false, 500.f);
}

void ATowerActorBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UTowerEnemyInterface>()) return;
	
	SetActorTickEnabled(true);

	TObjectPtr<ATowerEnemyPawn> TargetActor = Cast<ATowerEnemyPawn>(OtherActor);
	
	TargetActor->OnDeath.AddDynamic(this, &ThisClass::OnTargetDeath);
	
	Targets.Add(TargetActor);
	
	if (TowerClasDefaultInfo->ProjectileClass && !FireRateTimer.IsValid())
	{
		GetWorldTimerManager().SetTimer(FireRateTimer, this, &ThisClass::Fire, FireRate, true, 0);
	}
}

void ATowerActorBase::OnActorOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->Implements<UTowerEnemyInterface>()) return;

	Targets.Remove(Cast<ATowerEnemyPawn>(OtherActor));
}

void ATowerActorBase::OnTargetDeath(ATowerEnemyPawn* EnemyPawn)
{
	Targets.Remove(EnemyPawn);
}

void ATowerActorBase::ActorSelected()
{
	TowerRangeDiskMesh->SetVisibility(true);
}

void ATowerActorBase::ActorDeselected()
{
	TowerRangeDiskMesh->SetVisibility(false);
}
