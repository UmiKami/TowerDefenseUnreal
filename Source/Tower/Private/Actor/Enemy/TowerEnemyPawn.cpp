// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Actor/Enemy/TowerEnemyPawn.h"
#include "Actor/Enemy/TowerEnemyPathActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"

// Sets default values
ATowerEnemyPawn::ATowerEnemyPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>("CapsuleCollision");
	SetRootComponent(CapsuleCollision);
	
	PawnSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("PawnSkeletalMesh");
	PawnSkeletalMesh->SetupAttachment(RootComponent);
	
	PawnMovementComponent = CreateDefaultSubobject<UPawnMovementComponent>("PawnMovementComponent");
}

void ATowerEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		PawnAIController = AIController;
	}
}

void ATowerEnemyPawn::MoveActorAlongSpline()
{
	if (!IsValid(PawnAIController) || !IsValid(PathToFollow)) return;
	
	IsMoving = PawnAIController->GetMoveStatus() == EPathFollowingStatus::Moving;
	
	if (!IsMoving)
	{
		// The lower the value the smoother
		CurrentSplineProgress += 0.1f;
		CurrentSplineProgress = FMath::Clamp(CurrentSplineProgress, 0.f, 1.f);
		
		const USplineComponent* SplinePath = PathToFollow->GetSplinePath();

		const FVector LocationAtDistanceAlongSpline = SplinePath->GetLocationAtDistanceAlongSpline(CurrentSplineProgress, ESplineCoordinateSpace::World);
		
		PawnAIController->MoveToLocation(LocationAtDistanceAlongSpline,5);
		UE_LOG(LogTemp, Warning, TEXT("Enemy pawn %s MOVING!!"), *GetName());
	}
}

void ATowerEnemyPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	MoveActorAlongSpline();
}

