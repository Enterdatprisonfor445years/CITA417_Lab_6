// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableTarget.h"

// Sets default values
AInteractableTarget::AInteractableTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractableTarget::BeginPlay()
{
	Super::BeginPlay();
	
	// Save our initial spawning position as our baseline ground floor
	StartLocation = GetActorLocation();

	// Calculate exactly where the roof is based on the designer's input
	TargetLocation = StartLocation + MoveDistance;
}

// Called every frame
void AInteractableTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Pick our destination based on the active state
	FVector CurrentDestination = bShouldRise ? TargetLocation : StartLocation;
	FVector CurrentLocation = GetActorLocation();

	// If we aren't at our destination yet, slide smoothly towards it
	if (!CurrentLocation.Equals(CurrentDestination, 1.0f))
	{
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, CurrentDestination, DeltaTime, MoveSpeed);
		SetActorLocation(NewLocation);
	}

}

void AInteractableTarget::TriggerActivate()
{
	bShouldRise = true;
	UE_LOG(LogTemp, Log, TEXT("%s: Interaction Activated! Rising initiated."), *GetName());
}

void AInteractableTarget::TriggerReset()
{
	bShouldRise = false;
	UE_LOG(LogTemp, Log, TEXT("%s: Reset Rule Triggered! Lowering initiated."), *GetName());
}
