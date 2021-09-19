// Copyright Jason ShuJi Chen 2021

#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	float PlayerReach = 200.f;

	UPROPERTY();
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	
	UPROPERTY();
	UInputComponent* InputComponent = nullptr;

	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetupInputComponent();
	
	// Return the first Actor within reach with physics body.
	FHitResult GetFirstPhysicsBodyInRange() const;

	// Return the player's reach 
	FVector GetPlayerReach() const;

	// Return the player's position in the world
	FVector GetPlayerWorldPosition() const;
};
