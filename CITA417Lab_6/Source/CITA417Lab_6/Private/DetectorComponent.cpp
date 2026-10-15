// Fill out your copyright notice in the Description page of Project Settings.
#include "DetectorComponent.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h" // Included to scan for the box trigger boundary


// Sets default values for this component's properties
UDetectorComponent::UDetectorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDetectorComponent::BeginPlay()
{
	Super::BeginPlay();

    // Look at our owning actor and find its attached trigger box volume
    AActor* Owner = GetOwner();
    if (Owner)
    {
        UBoxComponent* TriggerBox = Owner->FindComponentByClass<UBoxComponent>();

        // If a box is found, link our custom detection functions to its physics system
        if (TriggerBox)
        {
            TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &UDetectorComponent::OnOverlapBegin);
            TriggerBox->OnComponentEndOverlap.AddDynamic(this, &UDetectorComponent::OnOverlapEnd);
        }
        else
        {
            // Safety logging to warn designers in the output log window
            UE_LOG(LogTemp, Warning, TEXT("DetectorComponent on %s requires a UBoxComponent attached to fire overlap triggers!"), *Owner->GetName());
        }
    }
	
}


void UDetectorComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Ignore internal triggers hitting ourselves
    if (OtherActor && OtherActor != GetOwner())
    {
        // Safety check: Makes sure a designer actually hooked up a platform destination
        if (TargetPlatform)
        {
            TargetPlatform->TriggerActivate();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("%s has no TargetPlatform configured in the editor!"), *GetOwner()->GetName());
        }
    }
}

void UDetectorComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != GetOwner())
    {
        // Implementation of our Reset Rule extension
        if (TargetPlatform)
        {
            TargetPlatform->TriggerReset();
        }
    }
}

