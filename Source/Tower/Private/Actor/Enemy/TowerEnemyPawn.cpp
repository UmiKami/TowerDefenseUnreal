// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Actor/Enemy/TowerEnemyPawn.h"
#include "Actor/Enemy/TowerEnemyPathActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Interaction/TowerPlayerInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

// Sets default values
ATowerEnemyPawn::ATowerEnemyPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>("CapsuleCollision");
	SetRootComponent(CapsuleCollision);
	
	PawnSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("PawnSkeletalMesh");
	PawnSkeletalMesh->SetupAttachment(RootComponent);
	
	PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovementComponent");
	
}

FVector ATowerEnemyPawn::GetCurrentLocation() const
{
	return GetActorLocation();
}

bool ATowerEnemyPawn::IsValidPtr() const
{
	return IsValid(this);
}

void ATowerEnemyPawn::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                const FHitResult& SweepResult)
{
	TScriptInterface<ITowerPlayerInterface> PlayerStronghold = OtherActor;
	
	if (!PlayerStronghold) return;
	
	UGameplayStatics::ApplyDamage(OtherActor, Damage, GetController(), this, {});
}

void ATowerEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
	
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		PawnAIController = AIController;
		checkf(PawnAIController, TEXT("AI Controller not set."))
		UE_LOG(LogTemp, Warning, TEXT("%s is %d"), *PawnAIController.GetName(), IsValid(PawnAIController))
	}
	
	PathToFollow = Cast<ATowerEnemyPathActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ATowerEnemyPathActor::StaticClass()));
	
	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
}

float ATowerEnemyPawn::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Health = FMath::Clamp(Health - DamageAmount, 0.f, MaxHealth);
	
	if (Health <= 0.f)
	{
		OnDeath.Broadcast(this);
		// TODO: Play death animation in BP
		// TODO: Destroy in BP
	}
	
	return DamageAmount;
}

void ATowerEnemyPawn::MoveActorAlongSpline()
{
	if (!IsValid(PathToFollow)) return;
	if (CurrentDistanceTravelled >= PathToFollow->GetSplinePath()->GetSplineLength()) return;

	const USplineComponent* SplinePath = PathToFollow->GetSplinePath();
	const float TotalLength = SplinePath->GetSplineLength();

	// Advance by distance per second, not arbitrary float steps
	CurrentDistanceTravelled += MovementSpeed * GetWorld()->GetDeltaSeconds();
	CurrentDistanceTravelled = FMath::Clamp(CurrentDistanceTravelled, 0.f, TotalLength);

	const FVector TargetLocation = SplinePath->GetLocationAtDistanceAlongSpline(
		CurrentDistanceTravelled,
		ESplineCoordinateSpace::World
	);

	FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
	Direction.Z = 0.f;
	
	SetActorRotation(Direction.Rotation());
	
	AddMovementInput(Direction, 1.f);
}

void ATowerEnemyPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	MoveActorAlongSpline();
}

