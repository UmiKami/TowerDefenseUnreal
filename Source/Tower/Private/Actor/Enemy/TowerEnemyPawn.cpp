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

void ATowerEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		PawnAIController = AIController;
		checkf(PawnAIController, TEXT("AI Controller not set."))
		UE_LOG(LogTemp, Warning, TEXT("%s is %d"), *PawnAIController.GetName(), IsValid(PawnAIController))
	}
	
	PathToFollow = Cast<ATowerEnemyPathActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ATowerEnemyPathActor::StaticClass()));
	
	
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
	AddMovementInput(Direction, 1.f);
}

void ATowerEnemyPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	MoveActorAlongSpline();
}

