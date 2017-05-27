// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "BatteryPickup.h"

// Sets default values for this actor's properties
ABatteryPickup::ABatteryPickup()
{
	GetMesh()->SetSimulatePhysics(true);

	// Base power lvl of the battery
	BatteryPower = 150.0f;
}

// Handles functionality upon a pickup being collected
void ABatteryPickup::wasCollected_Implementation()
{
	// Use the base pickup behavior
	Super::wasCollected_Implementation();

	// Destroy the battery
	Destroy();
}

// Reports the power lvl of the battery
float ABatteryPickup::GetPower()
{
	return BatteryPower;
}

