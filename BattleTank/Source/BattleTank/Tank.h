// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn //inheritance: ATank is a subtype of APawn which is a subtype of AActor
{
	GENERATED_BODY()

public:
	ATank();
	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	
	FTankDelegate OnDeath;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

private:
	void BeginPlay() override;

	// Return current health as a percentage of starting health between 0 ... 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;
};
