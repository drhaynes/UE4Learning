// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeTheRoom.h"
#include "Grabber.h"

UGrabber::UGrabber()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (!PhysicsHandle) {
        UE_LOG(LogTemp, Error, TEXT("%s: Missing physics handle component."), *GetOwner()->GetName());
    }

    PawnInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (PawnInputComponent) {
        
    } else {
        UE_LOG(LogTemp, Error, TEXT("%s: Missing input component."), *GetOwner()->GetName());
    }
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

