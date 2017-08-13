// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"



// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// 
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	// Find the owning Actor
	Owner->SetActorRotation(FRotator(0.0f, -60.0f, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	// Find the owning Actor
	
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		bIsDoorClosingOrClosed = false;
		DoorLastOpenTime = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("Opening Door"));
	}

	// Check if it's time to close the door
	if ((GetWorld()->GetTimeSeconds() - DoorLastOpenTime) > DoorCloseDelay && !bIsDoorClosingOrClosed)
	{
		bIsDoorClosingOrClosed = true;
		CloseDoor();
		UE_LOG(LogTemp, Warning, TEXT("Closing Door"));
	}
}

