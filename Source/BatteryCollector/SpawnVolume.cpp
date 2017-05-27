// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "SpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pickup.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the Box Component to represent the spawn volume
	whereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("whereToSpawn"));
	RootComponent = whereToSpawn;

	// Set spawn delay range
	spawnDelayRangeLow = 1.0f;
	spawnDelayRangeHigh = 4.5f;



}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::getRandomPointInVolume()
{
	FVector spawnOrgin = whereToSpawn->Bounds.Origin;
	FVector spawnExtent = whereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrgin, spawnExtent);

}

void ASpawnVolume::SetSpawningActive(bool bShouldSpawn)
{
	if(bShouldSpawn)
	{
		// Set the timer on Spawn Pickup
		spawnDelay = FMath::FRandRange(spawnDelayRangeLow, spawnDelayRangeHigh);
		GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume::spawnPickup, spawnDelay, false);
	}
	else
	{
		// clear the timer on Spawn Pickup
		GetWorldTimerManager().ClearTimer(spawnTimer);
	}
}

void ASpawnVolume::spawnPickup()
{
	// If we have set something to spawn
	if (whatToSpawn != NULL)
	{
		// Check for valid world
		UWorld* const world = GetWorld();
		if(world)
		{
			// Set spawn params
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = Instigator;

			// Get a random location to spawn at
			FVector spawnLocation = getRandomPointInVolume();

			// Get a random rotation for this spawned item
			FRotator spawnRotation;
			spawnRotation.Yaw = FMath::FRand() * 360.0f;
			spawnRotation.Pitch = FMath::FRand() * 360.0f;
			spawnRotation.Roll = FMath::FRand() * 360.0f;

			// Spawn the pickup
			APickup* const spawnedPickup = world->SpawnActor<APickup>(whatToSpawn, spawnLocation, spawnRotation, spawnParams);

			spawnDelay = FMath::FRandRange(spawnDelayRangeLow, spawnDelayRangeHigh);
			GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume::spawnPickup, spawnDelay, false);
		}
	}
}

