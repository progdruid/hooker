// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelPlayerController.h"

#include "BaseSurface.h"


ALevelPlayerController::ALevelPlayerController()
{
	
}

void ALevelPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ALevelPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	CurrentMouseCursor = EMouseCursor::Default;

	//get pawn info
	if (!LevelPawn || !bCanControl)
		return;
	const FVector pawnPosition = LevelPawn->GetActorTransform().GetLocation();
	
	//get mouse info
	FVector mousePosition, mouseDirection;
	const bool foundMouse = DeprojectMousePositionToWorld(mousePosition, mouseDirection);
	if (!foundMouse)
		return;
	
	//calculate hook direction
	const float t = -mousePosition.X / mouseDirection.X; // factor
	FVector positionOnPlane = mousePosition + mouseDirection * t; // getting the point on the x = 0 plane
	positionOnPlane.X = 0.f;
	Direction = positionOnPlane - pawnPosition;


	if (!UsedHook)
		return;
	
	//raycast
	FHitResult result;
	FCollisionQueryParams collisionQuery;
	collisionQuery.AddIgnoredActor(LevelPawn);
	const bool foundHit = GetWorld()->LineTraceSingleByChannel(
		result,
		pawnPosition,
		pawnPosition + Direction * UsedHook.GetDefaultObject()->GetMaxHookableDistance() * 1.2f,
		ECC_Visibility,
		collisionQuery);

	//interactiveness evaluation
	const ABaseSurface* surface = Cast<ABaseSurface>(result.GetActor());
	const bool hitInteractive = foundHit && surface
		&& result.Distance < UsedHook.GetDefaultObject()->GetMaxHookableDistance()
		&& InteractivityTagQuery.Matches(surface->GetGameplayTagContainer());
	if (hitInteractive)
		CurrentMouseCursor = EMouseCursor::Hand;
}

void ALevelPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	LevelPawn = Cast<ALevelPawn>(InPawn);
}

void ALevelPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	
	LevelPawn = nullptr;
}

void ALevelPlayerController::CallLaunch()
{
	if (!LevelPawn || !bCanControl)
		return;
	
	LevelPawn->LaunchHook(Direction);
}

void ALevelPlayerController::CallRevoke()
{
	if (!LevelPawn || !bCanControl)
		return;

	LevelPawn->RevokeHook();
}

void ALevelPlayerController::UpdatePullAxis(bool _isPulling)
{
	if (!LevelPawn || !bCanControl)
		return;

	LevelPawn->UpdateIsPulling(_isPulling);
}

void ALevelPlayerController::SetControllability(bool _value)
{
	bCanControl = _value;
}

