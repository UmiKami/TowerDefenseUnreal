// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Actor/TowerProjectileBase.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ATowerProjectileBase::ATowerProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("SphereCollision");
	BoxCollision->SetCollisionProfileName(TEXT("Projectile"));
	BoxCollision->SetupAttachment(RootComponent);
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	ProjectileMesh->SetupAttachment(BoxCollision);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	

}

void ATowerProjectileBase::InitProjectileParams(float Damage, float InitSpeed, float InMaxSpeed, TScriptInterface<ITowerEnemyInterface> InTargetEnemy)
{
	this->Damage = Damage;
	TargetEnemy = InTargetEnemy;
}

void ATowerProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnHit);
	
	// SetLifeSpan(10.f);
}

void ATowerProjectileBase::TryLaunchAtTarget(FVector StartLocation, FVector EndLocation, float Damage, bool bHasArch, float ArcHeight)
{
	if (Damage <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Damage cannot be 0 or less."))
		return;
	}
	
	
	LaunchAtTarget(StartLocation, EndLocation, Damage, bHasArch, ArcHeight);
}

void ATowerProjectileBase::LaunchAtTarget(FVector StartLocation, FVector EndLocation, float Damage, bool bHasArch, float ArcHeight)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile %s Launched from %s."), *GetName(), *StartLocation.ToString());
	

}

void ATowerProjectileBase::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile Just Hit"));
}
