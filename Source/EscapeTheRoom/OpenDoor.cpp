// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeTheRoom.h"
#include "OpenDoor.h"

UOpenDoor::UOpenDoor() {
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::BeginPlay() {
	Super::BeginPlay();

    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::TickComponent(float DeltaTime,
                              ELevelTick TickType,
                              FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
        OpenDoor();
    }
}

void UOpenDoor::OpenDoor() {
    auto Owner = GetOwner();
    FRotator Rotation = FRotator(0.f, -60.f, 0.f);
    Owner->SetActorRotation(Rotation);
}
