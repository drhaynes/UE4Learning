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
    Owner = GetOwner();
}

void UOpenDoor::TickComponent(float DeltaTime,
                              ELevelTick TickType,
                              FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    const float TimeNow = GetWorld()->GetTimeSeconds();

    if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
        SetDoorRotation(-OpenAngle);
        LastDoorOpenTime = TimeNow;
    }

    if (TimeNow - LastDoorOpenTime > DoorCloseDelay) {
        SetDoorRotation(0.f);
    }
}

void UOpenDoor::SetDoorRotation(float NewRotation) {
    Owner->SetActorRotation(FRotator(0.f, NewRotation, 0.f));
}
