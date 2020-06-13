// Fill out your copyright notice in the Description page of Project Settings.


#include "Hook.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UHook::UHook()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UHook::GetComponentAndBind() 
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	inputComponents = GetOwner()->FindComponentByClass<UInputComponent>();
	inputComponents->BindAction("Grab", IE_Pressed, this, &UHook::Grab);
	inputComponents->BindAction("Grab", IE_Released, this, &UHook::Release);
}
void UHook::Grab()
{
	auto hitResult = GetPhysicsBodyInReach();
	auto grabComponent = hitResult.GetComponent();
	auto actorHit = hitResult.GetActor();

	if (actorHit) 
	{
		physicsHandle->GrabComponentAtLocation
		(
			grabComponent, NAME_None, grabComponent->GetOwner()->GetActorLocation()
		);
	}

}
void UHook::Release()
{
	physicsHandle->ReleaseComponent();
}
FHitResult UHook::GetPhysicsBodyInReach()
{
	FCollisionQueryParams traceParameters(FName(TEXT("")), false ,GetOwner());

	FHitResult hitResult;
	GetWorld()->LineTraceSingleByObjectType(
		hitResult, GetReachStart(), GetReachEnd(),FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParameters
		);

	return hitResult;
}
FVector UHook::GetReachStart()
{
	FVector playerViewPoint;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		playerViewPoint,playerViewPointRotation
	);
	return playerViewPoint;
}
FVector UHook::GetReachEnd()
{
	FVector playerViewPoint;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		playerViewPoint, playerViewPointRotation
	);
	FVector lineTraceEnd = playerViewPoint + playerViewPointRotation.Vector() * reach;
	return lineTraceEnd;
}
// Called when the game starts
void UHook::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GetComponentAndBind();
}


// Called every frame
void UHook::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (physicsHandle->GrabbedComponent) {
		physicsHandle->SetTargetLocation(GetReachEnd());
	}
}

