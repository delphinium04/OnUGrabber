// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Interactable.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	// ...

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckObjectReach();
}

void UGrabber::OnGrabKeyClicked()
{
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("No Physics Handle in Player"));
		return;
	}

	if (IsGrabbed)
		Release();
	else
		Grab();
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Display, TEXT("Try Grab"));
	FHitResult HitResult;
	if (GetInteractableInReach(HitResult)) {
		UPrimitiveComponent* Root = HitResult.GetComponent();
		Root->WakeAllRigidBodies();

		PhysicsHandle->GrabComponentAtLocationWithRotation(
			Root,
			NAME_None,
			HitResult.ImpactPoint,
			Root->GetComponentRotation());
		IsGrabbed = true;
	}
}

bool UGrabber::GetInteractableInReach(FHitResult& OutHitResult)
{
	FVector StartPos = GetComponentLocation();
	FVector EndPos = StartPos + GetForwardVector() * GrabMaxDistance;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	if (GetWorld()->LineTraceSingleByChannel(OutHitResult, StartPos, EndPos, ECC_Visibility, CollisionParams)) {
		if (OutHitResult.GetActor()->FindComponentByClass<UInteractable>() != nullptr)
			return true;
	}

	return false;
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Release Grab"));
	PhysicsHandle->ReleaseComponent();
	IsGrabbed = false;
}

void UGrabber::CheckObjectReach()
{
	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * GrabDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}
