// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Hook.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_3D_PLATFORMER_API UHook : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHook();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float reach = 100.f;
	UPhysicsHandleComponent* physicsHandle = nullptr;
	UInputComponent* inputComponents = nullptr;
	void GetComponentAndBind();
	void Grab();
	void Release();
	FHitResult GetPhysicsBodyInReach();
	FVector GetReachStart();
	FVector GetReachEnd();
};
