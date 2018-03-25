// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "GameFramework/Actor.h" //could be deleted
#include "TankPlayerController.generated.h" //must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	ATank * GetControlledTank() const;
	void BeginPlay() override;
	void AimTowardsCrosshair();

public:
	virtual void Tick(float DeltaTime) override;

};
