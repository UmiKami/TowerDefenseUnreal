// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Actor/TowerPlayerStronghold.h"

#include "Components/BoxComponent.h"
#include "Game/TowerGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TowerPlayerCharacter.h"
#include "Player/TowerPlayerState.h"


// Sets default values
ATowerPlayerStronghold::ATowerPlayerStronghold()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	SetRootComponent(BoxCollision);
	
	StrongholdMesh = CreateDefaultSubobject<UStaticMeshComponent>("StrongholdMesh");
	StrongholdMesh->SetupAttachment(RootComponent);
}

AActor* ATowerPlayerStronghold::GetActorRef()
{
	return this;
}

void ATowerPlayerStronghold::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorTickEnabled(false);
	
	TowerPlayerState = Cast<ATowerPlayerState>(UGameplayStatics::GetPlayerState(this, 0));
	checkf(TowerPlayerState, TEXT("Unable to access Tower Player State from stronghold."));
	
	TowerGameState = Cast<ATowerGameState>(UGameplayStatics::GetGameState(this)); 
	checkf(TowerPlayerState, TEXT("Unable to access Tower Game State from stronghold."));
}

// Called every frame
void ATowerPlayerStronghold::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ATowerPlayerStronghold::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	TowerPlayerState->AddHealth(-DamageAmount);
	PostTakeDamageAction();
	return DamageAmount;
}



