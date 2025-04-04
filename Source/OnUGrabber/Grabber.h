// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grabber.generated.h"

class UInteractable;
class UPhysicsHandleComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ONUGRABBER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnGrabKeyClicked();

	UPROPERTY(EditAnywhere)
	float GrabMaxDistance = 500.0f;

	UPROPERTY(EditAnywhere)
	float GrabDistance = 300.0f;

private:
	bool IsGrabbed = false;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	void Grab();
	void Release();

	bool GetInteractableInReach(FHitResult& OutHitResult);
	void CheckObjectReach();
};
