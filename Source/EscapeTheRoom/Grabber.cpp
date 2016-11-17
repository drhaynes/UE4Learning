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
    if (!PhysicsHandle) {
        return;
    } else if (PhysicsHandle->GrabbedComponent) {
        PhysicsHandle->SetTargetLocation(GetGrabLineFromPlayer().End);
    }
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
    auto Line = GetGrabLineFromPlayer();
    FHitResult Hit;
    FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(Hit, Line.Start, Line.End, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
    return Hit;
}

const FLine UGrabber::GetGrabLineFromPlayer() {
    auto PlayerController = GetWorld()->GetFirstPlayerController();
    FLine Line;
    FRotator Rotation;
    PlayerController->GetPlayerViewPoint(Line.Start, Rotation);
    Line.End = Line.Start + (Rotation.Vector() * Reach);
    return Line;
}

void UGrabber::Grab()
{
    auto ComponentToGrab = GetFirstPhysicsBodyInReach().GetComponent();

    if (ComponentToGrab) {
        PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
    }
}

void UGrabber::Release()
{
    if (PhysicsHandle) {
        PhysicsHandle->ReleaseComponent();
    }
}
