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

	// FRotator DoorOpen(0.f, 90.f, 0.f);
	// GetOwner()->SetActorRotation(DoorOpen);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("The Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);
	
	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator DoorOpen(0.f, 0, 0.f);

	DoorOpen.Yaw = FMath::Lerp(CurrentYaw, TargetYaw, 0.02f);
	// FInterpTo is smoother, framerate independent.
	// DoorOpen.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2);
	GetOwner()->SetActorRotation(DoorOpen);
}

