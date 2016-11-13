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
    ConfigureComponents();
}

void UGrabber::ConfigureComponents() {
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (!PhysicsHandle) {
        UE_LOG(LogTemp, Error, TEXT("%s: Missing physics handle component."), *GetOwner()->GetName());
    }

    PawnInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (PawnInputComponent) {
        PawnInputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        PawnInputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    } else {
        UE_LOG(LogTemp, Error, TEXT("%s: Missing input component."), *GetOwner()->GetName());
    }
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (PhysicsHandle->GrabbedComponent) {
        auto PlayerController = GetWorld()->GetFirstPlayerController();
        FVector Position;
        FRotator Rotation;
        PlayerController->GetPlayerViewPoint(Position, Rotation);
        FVector LineTraceEnd = Position + (Rotation.Vector() * Reach);

        PhysicsHandle->SetTargetLocation(LineTraceEnd);
    }
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
    auto PlayerController = GetWorld()->GetFirstPlayerController();
    FVector Position;
    FRotator Rotation;
    PlayerController->GetPlayerViewPoint(Position, Rotation);
    FVector LineTraceEnd = Position + (Rotation.Vector() * Reach);

    FHitResult Hit;
    FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(Hit, Position, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
    return Hit;
}

void UGrabber::Grab()
{
    UE_LOG(LogTemp, Warning, TEXT("GRABBBBY"));
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ThingHit = HitResult.GetActor();
    auto ComponentToGrab = HitResult.GetComponent();

    if (ThingHit) {
        UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *ThingHit->GetName());
    }

    if (ComponentToGrab) {
        PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
    }
}

void UGrabber::Release()
{
    UE_LOG(LogTemp, Warning, TEXT("DROPPED"));
    PhysicsHandle->ReleaseComponent();
}
