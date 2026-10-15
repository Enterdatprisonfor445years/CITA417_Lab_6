// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableTarget.generated.h"

UCLASS()
class CITA417LAB_6_API AInteractableTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void TriggerActivate();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void TriggerReset();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	FVector MoveDistance = FVector(0.0f, 0.0f, 300.0f); // Default: rise 300 units up

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MoveSpeed = 2.0f;

private:
	// Internal spatial tracking
	FVector StartLocation;
	FVector TargetLocation;

	// True means moving to target, false means resetting to start
	bool bShouldRise = false;
};
