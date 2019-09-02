// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include <GameFramework/Actor.h>

#define OUT

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

	Owner = GetOwner();
	Angle = Owner->GetActorRotation();	

	if (!PressurePlate) { UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate!"), *(GetOwner()->GetName())) }
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOnPlate() > TriggerMass)
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
		CloseDoor();

}

float UOpenDoor::GetTotalMassOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> OvelapingActors;

	if (!PressurePlate) { return TotalMass; }
	///Finding all ovelaping actors
	PressurePlate->GetOverlappingActors(OUT OvelapingActors);

	for (auto* Actor : OvelapingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

void UOpenDoor::OpenDoor()
{
	FRotator NewRotatrion = Angle;
	NewRotatrion.Pitch += OpenAngle;
	Owner->SetActorRotation(NewRotatrion);
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(Angle);
}