// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableTarget.h"
#include "DetectorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CITA417LAB_6_API UDetectorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDetectorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	// Custom functions to bind to collision overlapping signatures
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	// Exposed designer-facing pointer setting to pick our target platform instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction System")
	AInteractableTarget* TargetPlatform;
		
};
