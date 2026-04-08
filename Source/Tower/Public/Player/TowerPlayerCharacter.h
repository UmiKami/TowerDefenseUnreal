// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TowerPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;
class UInputAction;
struct FInputActionValue;


/**
 * @brief Representation of the player character in the world. 
 * @ingroup Tower
 *	
 * @note Invisible by default for this tower defense game.
 */
UCLASS()
class TOWER_API ATowerPlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	ATowerPlayerCharacter();

protected:
	virtual void BeginPlay() override;

	/**
	 * @brief Root component which allows viewing camera to go up and down based on landscape.
	 * @note Root is likely to be locked in the Z axis at such height it does not collide with anything.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereCollision;
	
	/**
	 * @see USpringArmComponent
	 */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArm;
	
	/**
	 * @see UCameraComponent
	 */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> PlayerCamera;

	/**
	 * @brief Movement input action, normally WASD on keyboard
	 */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> MoveAction;
	
	/**
	 * @brief This will be used to interact with UI and world objects alike at runtime.
	 */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> LeftClickAction;
	
public:
	/**
	 * @brief Only used to bind actions that are unique to the GameplayLoop, e.g. Move, Zoom, click and drag.
	 * @param PlayerInputComponent 
	 */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	/**
	 * @brief Moves the pawn using SimplePawnMovementComponent added on blueprint
	 * @param Value 
	 */
	void Move(const FInputActionValue& Value);
};
