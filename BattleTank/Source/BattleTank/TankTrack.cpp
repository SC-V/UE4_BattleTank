// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

void UTankTrack::SetThrottle(float Throttle)
{
	// Debug log
	//auto Time = GetWorld()->GetTimeSeconds();
	//auto Name = GetName();
	//UE_LOG(LogTemp, Error, TEXT("%s : Throttle: %f"), *Name, Throttle);

	// TODO clamp actual throttle value

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}


