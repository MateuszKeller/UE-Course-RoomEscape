// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	if (PhysicsHandle)
	{
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component!"), *(GetOwner()->GetName()))
	}
		
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector ViewLocation;
	FRotator VievRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT ViewLocation, OUT VievRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s; Rocation: %s"), *ViewLocation.ToString(), *VievRotation.ToString())

	FVector LineTraceEnd = ViewLocation + VievRotation.Vector() * Reach;
	FCollisionQueryParams TraceParameteres(FName(TEXT("")), false, GetOwner());
	if (DrawDebug)
	{
		
		DrawDebugLine(GetWorld(), ViewLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);
	}

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, ViewLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameteres);

	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit %s"), *(ActorHit->GetName()))
	}
}

