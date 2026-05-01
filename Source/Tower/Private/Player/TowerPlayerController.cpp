// Copyright UmiKami (Ernesto Gonzalez) © 2026

#include "Player/TowerPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actor/TowerActorBase.h"
#include "Actor/Tower/TowerActorGhostMirror.h"
#include "Actor/Tower/TowerSnapArea.h"
#include "Blueprint/UserWidget.h"
#include "Data/TowerClassInfo.h"
#include "Player/TowerPlayerState.h"
#include "Game/TowerGameMode.h"
#include "Game/TowerGameState.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/TowerUserWidget.h"
#include "UserInterface/WidgetController/TowerWidgetController.h"

ATowerPlayerController::ATowerPlayerController()
{
	bShowMouseCursor = true;
}

void ATowerPlayerController::AttachMeshToFollowCursor(ETowerClass TowerClass, int32 TowerLevel)
{
	if (!TowerClassInfo) return;

	if (GhostMesh)
	{
		GhostMesh->Destroy();
		GhostMesh = nullptr;
	}

	FVector WorldLocation;
	FVector WorldDirection;

	DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FHitResult Hit;
	FVector End = WorldLocation + WorldDirection * 10000.f;

	GetWorld()->LineTraceSingleByChannel(
		Hit,
		WorldLocation,
		End,
		ECC_Visibility
	);

	FVector TowerSpawnLocation = Hit.bBlockingHit ? Hit.ImpactPoint : End;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GhostMesh = GetWorld()->SpawnActor<ATowerActorGhostMirror>(
		TowerClassInfo->GhostActorClass,
		TowerSpawnLocation,
		FRotator::ZeroRotator,
		Params
	);

	USkeletalMeshComponent* MeshComp = GhostMesh->Mesh;
	GhostMesh->TowerClass = TowerClass;
	GhostMesh->Level = TowerLevel;

	MeshComp->SetSkeletalMesh(
		*TowerClassInfo->TowerClassInformation[TowerClass].SkeletalMeshComponentPerLevel.Find(TowerLevel));
	MeshComp->SetMaterial(0, TowerClassInfo->GhostMaterialInstance);
}

void ATowerPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!GhostMesh || GhostMesh->IsPendingKillPending()) return;

	FVector WorldLocation;
	FVector WorldDirection;

	DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FHitResult Hit;
	FVector End = WorldLocation + WorldDirection * 10000.f;

	GetWorld()->LineTraceSingleByChannel(
		Hit,
		WorldLocation,
		End,
		ECC_Visibility
	);

	const FVector NextLocation = Hit.bBlockingHit ? Hit.ImpactPoint : End;

	// DrawDebugSphere(GetWorld(), NextLocation, 32, 12, FColor::Green, false, 5);

	AActor* HitActor = Hit.GetActor();

	// TODO This can be optimized, avoid casting on Tick
	ATowerSnapArea* HitSnapArea = IsValid(HitActor) ? Cast<ATowerSnapArea>(HitActor) : nullptr;

	if (HitSnapArea && !HitSnapArea->bOccupied)
	{
		const FAttachmentTransformRules AttachmentTransformRules{
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepWorld,
			EAttachmentRule::KeepWorld,
			false
		};

		GhostMesh->bSnappedToArea = GhostMesh->AttachToActor(HitActor, AttachmentTransformRules);
		GhostMesh->CurrentSnapArea = HitSnapArea;
	}

	if (!IsValid(HitActor) || IsValid(HitActor) && !HitActor->ActorHasTag("SnapArea"))
	{
		GhostMesh->bSnappedToArea = false;

		FDetachmentTransformRules DetachmentTransformRules{
			EDetachmentRule::KeepWorld,
			EDetachmentRule::KeepWorld,
			EDetachmentRule::KeepWorld,
			false
		};

		GhostMesh->DetachFromActor(DetachmentTransformRules);
		GhostMesh->CurrentSnapArea = nullptr;
	}

	if (GhostMesh->bSnappedToArea) return;

	GhostMesh->SetActorLocation(NextLocation);
}

void ATowerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	checkf(DefaultMappingContext, TEXT("Default input mapping context not set in Tower Player Controller."));

	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(EscapeAction, ETriggerEvent::Started, this, &ThisClass::OnEscape);
		EnhancedInputComponent->BindAction(RightMouseAction, ETriggerEvent::Started, this, &ThisClass::OnRMB);
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Started, this, &ThisClass::OnLMB);
	}
}

void ATowerPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UUserWidget* PlayerHUDUserWidget = CreateWidget(this, PlayerHUDClass);
	PlayerHUD = Cast<UTowerUserWidget>(PlayerHUDUserWidget);

	UTowerWidgetController* PlayerHUDWidgetController = NewObject<UTowerWidgetController>(this, WidgetControllerClass);

	ATowerGameMode* GameMode = Cast<ATowerGameMode>(UGameplayStatics::GetGameMode(this));

	const FWidgetControllerParams Params{
		this,
		GetPlayerState<ATowerPlayerState>(),
		Cast<ATowerGameState>(UGameplayStatics::GetGameState(this)),
		GameMode
	};
	PlayerHUDWidgetController->SetWidgetControllerParams(Params);

	PlayerHUD->AddToViewport();
	PlayerHUD->SetWidgetController(PlayerHUDWidgetController);

	GameMode->OnGameOverSignature.AddDynamic(this, &ThisClass::OnGameOver);
}

void ATowerPlayerController::OnEscape(const FInputActionValue& Value)
{
	if (GhostMesh)
	{
		GhostMesh->Destroy();
		GhostMesh = nullptr;
	}
}

void ATowerPlayerController::OnRMB(const FInputActionValue& InputActionValue)
{
	if (GhostMesh)
	{
		GhostMesh->Destroy();
		GhostMesh = nullptr;
	}
}

void ATowerPlayerController::OnLMB(const FInputActionValue& InputActionValue)
{
	if (IsValid(GhostMesh) && GhostMesh->bSnappedToArea)
	{
		const FTransform NewTowerTransform
		{
			GhostMesh->GetActorLocation()
		};

		ATowerActorBase* Tower = GetWorld()->SpawnActorDeferred<ATowerActorBase>(
			TowerClassInfo->TowerActorBaseClass,
			NewTowerTransform,
			this,
			GetInstigator()
		);

		Tower->SetTowerLevel(GhostMesh->Level);
		Tower->SetTowerClass(GhostMesh->TowerClass);

		Tower->FinishSpawning(NewTowerTransform);

		if (Tower)
		{
			GhostMesh->CurrentSnapArea->bOccupied = true;
			GhostMesh->Destroy();
			GhostMesh = nullptr;
		}
	}
}

void ATowerPlayerController::OnGameOver()
{
	PlayerHUD->RemoveFromParent();
	
	if (IsValid(GhostMesh))
	{
		GhostMesh->Destroy();
		GhostMesh = nullptr;
	}

	UUserWidget* GameOverUserWidget = CreateWidget(this, GameOverWidgetClass);

	GameOverWidget = Cast<UTowerUserWidget>(GameOverUserWidget);

	UTowerWidgetController* GameOverWidgetController = NewObject<UTowerWidgetController>(this, WidgetControllerClass);
	const FWidgetControllerParams Params{
		this,
		GetPlayerState<ATowerPlayerState>(),
		Cast<ATowerGameState>(UGameplayStatics::GetGameState(this)),
		Cast<ATowerGameMode>(UGameplayStatics::GetGameMode(this))
	};
	GameOverWidgetController->SetWidgetControllerParams(Params);

	GameOverWidget->AddToViewport();
	GameOverWidget->SetWidgetController(GameOverWidgetController);
}
