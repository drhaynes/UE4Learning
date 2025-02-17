// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeTheRoom.h"
#include "OpenDoor.h"

UOpenDoor::UOpenDoor() {
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::BeginPlay() {
    if (!PressurePlate) {
        UE_LOG(LogTemp, Error, TEXT("%s: Missing pressure plate reference."), *GetOwner()->GetName());
    }
	Super::BeginPlay();
    Owner = GetOwner();
}

void UOpenDoor::TickComponent(float DeltaTime,
                              ELevelTick TickType,
                              FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    const float TimeNow = GetWorld()->GetTimeSeconds();

    if (GetTotalMassOfActorsOnPlate() > TriggerMass) {
        OnOpenRequest.Broadcast();
        LastDoorOpenTime = TimeNow;
    }

    if (TimeNow - LastDoorOpenTime > DoorCloseDelay) {
        SetDoorRotation(0.f);
    }
}

void UOpenDoor::SetDoorRotation(float NewRotation) {
    Owner->SetActorRotation(FRotator(0.f, NewRotation, 0.f));
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
    float TotalMass = 0.f;

    TArray<AActor*> OverlappingActors;
    if (!PressurePlate) { return TotalMass; }
    PressurePlate->GetOverlappingActors(OverlappingActors);

    for (auto actor : OverlappingActors) {
        TotalMass +=  actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }
    return TotalMass;
}