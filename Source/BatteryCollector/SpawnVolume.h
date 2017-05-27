// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The pickup to spawn
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class APickup> whatToSpawn;

	FTimerHandle spawnTimer;

	// Min spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float spawnDelayRangeLow;

	// Max spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float spawnDelayRangeHigh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Returns the whereToSpawn subobject
	FORCEINLINE class UBoxComponent* getWhereToSpawn() const { return whereToSpawn; }

	// Find a random point within the Box Component
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector getRandomPointInVolume();

	// Toggles whether the spawn volume should spawn pickups
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SetSpawningActive(bool bSHouldSpawn);

private:
	// Box component to specify where pickups should be spawned
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* whereToSpawn;

	// Handle spawning a new pickup
	void spawnPickup();
	
	// Actual/current spawn delay
	float spawnDelay;

};
