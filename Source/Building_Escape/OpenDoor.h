// Copyright Jason ShuJi Chen 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	void FindTriggerVolume();
	float TotalMassOfActors() const;
	void FindAudioComponent();

	bool OpenDoorSound = false;
	bool CloseDoorSound = true;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	float InitialYaw;
	float CurrentYaw;

	UPROPERTY(EditAnywhere);
	float MassToOpen = 50.f;

	UPROPERTY(EditAnywhere);
	float OpenSpeed = 2;

	UPROPERTY(EditAnywhere);
	float CloseSpeed = 2;

	UPROPERTY(EditAnywhere);
	float DoorCloseDelay = 2.f;

	UPROPERTY(EditAnywhere);
	float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere);
	ATriggerVolume* PressurePlate = nullptr;

	float DoorLastOpened = 0.f;

	UPROPERTY();
	UAudioComponent* AudioComponent = nullptr;
};
