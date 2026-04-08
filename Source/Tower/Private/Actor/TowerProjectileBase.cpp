// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Actor/TowerProjectileBase.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ATowerProjectileBase::ATowerProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SphereCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SphereCollision"));
	
	SphereCollision->SetCapsuleHalfHeight(15.f);
	SphereCollision->SetCapsuleRadius(15.f);
	SphereCollision->SetCollisionProfileName(TEXT("Projectile"));
	
	SetRootComponent(SphereCollision);
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 1.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = false;
}

void ATowerProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollision->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	
	SetLifeSpan(10.f);
}

void ATowerProjectileBase::LaunchAtTarget(FVector StartLocation, FVector EndLocation, float Damage, bool bHasArch, float ArcHeight)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile %s Launched from %s."), *GetName(), StartLocation.ToString());
}

void ATowerProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile %s Just Hit => %s."), *GetName(), *OtherActor->GetName());
}
