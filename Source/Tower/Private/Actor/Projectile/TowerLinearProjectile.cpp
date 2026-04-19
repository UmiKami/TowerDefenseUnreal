// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Actor/Projectile/TowerLinearProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Interaction/TowerEnemyInterface.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATowerLinearProjectile::ATowerLinearProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATowerLinearProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (!TargetEnemy || !TargetEnemy->IsValidPtr()) 
	{
		Destroy();
		return;
	}
	
	FVector Direction = (TargetEnemy->GetCurrentLocation() - GetActorLocation()).GetSafeNormal();
	FVector NewLocation = GetActorLocation() + Direction * 2000.f * DeltaSeconds;

	SetActorLocationAndRotation(NewLocation, Direction.Rotation(), true);
}

void ATowerLinearProjectile::InitProjectileParams(float InDamage, float InitSpeed, float InMaxSpeed, TScriptInterface<ITowerEnemyInterface> InTargetEnemy)
{
	Super::InitProjectileParams(InDamage, InitSpeed, InMaxSpeed, InTargetEnemy);
	

	
}

void ATowerLinearProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATowerLinearProjectile::LaunchAtTarget(FVector StartLocation, FVector EndLocation, float InDamage, bool bHasArch, float ArcHeight)
{
	Super::LaunchAtTarget(StartLocation, EndLocation, InDamage,  bHasArch, ArcHeight);
	

 }

void ATowerLinearProjectile::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnHit(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	
	if (OtherActor && OtherActor->Implements<UTowerEnemyInterface>())
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Enemy HIT Confirmed!"));
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetOwner()->GetInstigatorController(), GetOwner(), {});
		
		// TODO Play animation or VFX on hit and then destroy the projectile. Otherwise projectile will self destroy in 10 seconds due to SetLifeSpan(10.f) in Base class BeginPlay
		
		Destroy();
	}
}

