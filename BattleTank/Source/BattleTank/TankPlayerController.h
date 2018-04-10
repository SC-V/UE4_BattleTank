// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TankPlayerController.generated.h" //must be the last include
 
/**
 *  Responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	void BeginPlay() override;
	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector & HitLocation) const; 
	// Get look direction
	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;
	// Get look vector hit location
	bool GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const;
	// Move the turret towards crosshair (position defined by GetSightRayHitLocation)
	void AimTowardsCrosshair();
	
	UFUNCTION()
	void OnControlledTankDeath();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent * AimCompRef);

	virtual void SetPawn(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.35f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;
};
