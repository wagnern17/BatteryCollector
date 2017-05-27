// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// True when the pickup can be used, and false when pickup is deactivated
	bool bIsActive;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Rtn the mesh for the pickup
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }

	// Rtn if a pickup is active or not
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool isActive();

	// Allows other classes to safely change a pickup being active or not
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void setActive(bool NewPickupState);

	// Func to call when a pickup is collected
	UFUNCTION(BlueprintNativeEvent)
	void wasCollected();
	virtual void wasCollected_Implementation();


private:
	// Static mesh to represent the pickup in the level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh;
	
};
