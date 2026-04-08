// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Player/TowerPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"


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
	}
}

void ATowerPlayerCharacter::Move(const FInputActionValue& Value)
{
	AddMovementInput(Value.Get<FVector>());
}

