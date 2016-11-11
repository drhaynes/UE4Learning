// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeTheRoom.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	FVector Position;
	FRotator Rotation;
	PlayerController->GetPlayerViewPoint(Position, Rotation);
	
	FVector LineTraceEnd = Position + (Rotation.Vector() * Reach);
	DrawDebugLine(GetWorld(), Position, LineTraceEnd, FColor(255, 0, 0), false, 0.f, .0f, 5.f);

	FHitResult Hit;
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(Hit, Position, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

	auto ThingHit = Hit.Actor;

	if (ThingHit != nullptr) {
		auto Name = Hit.Actor->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Name);
	}
}

