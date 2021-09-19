// Copyright Jason ShuJi Chen 2021

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

// Macro for marking out parameters
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	FindPhysicsHandle();
	SetupInputComponent();
}

// Checking for physics handle component
void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("NO PHYSICS HANDLE COMPONENT FOUND ON %s! "), *GetOwner()->GetName());
	}
}

// Checking for input component
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("NO INPUT COMPONENT FOUND ON %s!"), *GetOwner()->GetName());
	}
	else
	{
		// Binding the action to the keybind set in the project settings.
		InputComponent->BindAction("Interact", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Interact", IE_Released, this, &UGrabber::Release);
	}
}

FVector UGrabber::GetPlayerWorldPosition() const
{
	// Get players viewport
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}

FVector UGrabber::GetPlayerReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * PlayerReach;
}

// Grab function
void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInRange();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();
	// TODO attach physics handle.
	if (ActorHit)
	{	if(!PhysicsHandle){return;}
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None, 
			GetPlayerReach()
		);
	}
}

// Release function
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release Pressed!"));
	// TODO remove/release the physics handle.
	if(!PhysicsHandle){return;}
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached
	if(!PhysicsHandle){return;}
	if (PhysicsHandle->GrabbedComponent)
	{
		// Move the object we are holding.
		PhysicsHandle->SetTargetLocation(GetPlayerReach());
	}
	/* DEBUG: Draw a line from player showing the reach
	 DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0,
		1.f
	); */
}

FHitResult UGrabber::GetFirstPhysicsBodyInRange() const
{
	// Ray-cast out to a certain distance
	FHitResult Hit;
	FCollisionQueryParams TraceParams(
		FName(TEXT("")),
		false,
		GetOwner()
	);

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerWorldPosition(),
		GetPlayerReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	// See what it hits
	AActor* TargetActor = Hit.GetActor();
	
	// **For DEBUGGING** 
	if (TargetActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *TargetActor->GetName());
	}
	return Hit;
}