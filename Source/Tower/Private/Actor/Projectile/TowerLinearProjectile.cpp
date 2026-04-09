// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Actor/Projectile/TowerLinearProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Interaction/TowerEnemyInterface.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATowerLinearProjectile::ATowerLinearProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATowerLinearProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATowerLinearProjectile::LaunchAtTarget(FVector StartLocation, FVector EndLocation, float Damage, float InitSpeed, float InMaxSpeed, bool bHasArch, float ArcHeight)
{
	Super::LaunchAtTarget(StartLocation, EndLocation, Damage, InitSpeed, InMaxSpeed, bHasArch, ArcHeight);
		
	if (bHasArch) return;
	
	ProjectileMovementComponent->InitialSpeed = InitSpeed;
	ProjectileMovementComponent->MaxSpeed = InMaxSpeed;
	
	this->Damage = Damage;
 }

void ATowerLinearProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	
	if (OtherActor->Implements<UTowerEnemyInterface>())
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), GetOwner(), {});
		
		// TODO Play animation or VFX on hit and then destroy the projectile. Otherwise projectile will self destroy in 10 seconds due to SetLifeSpan(10.f) in Base class BeginPlay
	}
}

