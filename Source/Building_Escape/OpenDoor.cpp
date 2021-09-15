// Copyright Jason ShuJi Chen 2021

#include "GameFramework/Actor.h"
#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// float MyFloat = 90.f;
	
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	FRotator DoorOpen = {0.f, 90.f, 0.f};
	// FRotator DoorOpen = FRotator().Add(0.f, MyFloat, 0.f);
	// CurrentRotation.Yaw = MyFloat;

	GetOwner()->SetActorRotation(DoorOpen);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

