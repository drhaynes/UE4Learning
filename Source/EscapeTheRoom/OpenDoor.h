// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ESCAPETHEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime,
                               ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(VisibleAnywhere)
    float OpenAngle = 90.f;

    UPROPERTY(EditAnywhere)
    ATriggerVolume *PressurePlate = nullptr;

    UPROPERTY(EditAnywhere)
    float DoorCloseDelay = .5f;

    float LastDoorOpenTime;

    AActor *Owner = nullptr;

    UPROPERTY(EditAnywhere)
    float TriggerMass = 30.f;

    UPROPERTY(BlueprintAssignable)
    FOnOpenRequest OnOpenRequest;

    void SetDoorRotation(float NewRotation);
    float GetTotalMassOfActorsOnPlate();
};
