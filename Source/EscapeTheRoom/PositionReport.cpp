// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeTheRoom.h"
#include "PositionReport.h"

UPositionReport::UPositionReport() {
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UPositionReport::BeginPlay() {
	Super::BeginPlay();
    auto Name = GetOwner()->GetName();
    auto PositionText = GetOwner()->GetTransform().GetLocation().ToString();
    UE_LOG(LogTemp, Warning, TEXT("Position report is aliiiive on %s at %s"), *Name, *PositionText);
}

void UPositionReport::TickComponent(float DeltaTime,
                                    ELevelTick TickType,
                                    FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
