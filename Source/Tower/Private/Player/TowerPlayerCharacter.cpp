// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Player/TowerPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "KismetTraceUtils.h"
#include "Interaction/TowerHighlightInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/TowerPlayerController.h"


ATowerPlayerCharacter::ATowerPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereRoot");
	
	SetRootComponent(SphereCollision);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	PlayerCamera->SetupAttachment(SpringArm);
}

void ATowerPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ATowerPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Started, this, &ThisClass::LMouseButtonPressed);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &ThisClass::LMouseButtonReleased);
	}
}

void ATowerPlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector WorldDirection = Value.Get<FVector>();
	
	AddMovementInput(WorldDirection, 200);
}

void ATowerPlayerCharacter::DeselectCurrentlySelectedActors()
{
	for (auto HighlightedActor : SelectedActors)
	{
		HighlightedActor->ActorDeselected();
	}	
		
	SelectedActors.Empty();
}

void ATowerPlayerCharacter::LMouseButtonPressed(const FInputActionValue& Value)
{

	ATowerPlayerController* TowerPlayerController = Cast<ATowerPlayerController>(GetController());
	
	float PositionX = 0.f;
	float PositionY = 0.f;

	TowerPlayerController->GetMousePosition(PositionX, PositionY);

	FVector2D MousePosition = {PositionX, PositionY};

	FVector WorldPosition = {};
	FVector WorldDirection = {};

	UGameplayStatics::DeprojectScreenToWorld(TowerPlayerController, MousePosition, WorldPosition, WorldDirection);

	const FVector EndPoint = WorldPosition + WorldDirection * 5000;

	FHitResult OutHit;
	
	// ECC_GameTraceChannel1 = Tower collision trace channel
	GetWorld()->LineTraceSingleByChannel(OutHit, WorldPosition, EndPoint, ECC_GameTraceChannel1);

	AActor* ActorHit = OutHit.GetActor();
	
	if (const TScriptInterface<ITowerHighlightInterface> HighlightableActor = ActorHit)
	{
		DeselectCurrentlySelectedActors();
		
		HighlightableActor->ActorSelected();
		
		SelectedActors.Add(HighlightableActor);
	} else
	{
		DeselectCurrentlySelectedActors();
	}
}

void ATowerPlayerCharacter::LMouseButtonReleased(const FInputActionValue& Value)
{
}

