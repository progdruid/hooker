// Fill out your copyright notice in the Description page of Project Settings.


#include "Pullable.h"

// Add default functionality here for any IPullable functions that are not pure virtual.

void IPullable::AddPull(FVector _pull)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Red, FString("Pulled, lol"));
}

FVector IPullable::GetLocation()
{
	return FVector(0, 0, 0);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Red, FString("Got location, lol"));
}

void IPullable::ToggleGravity(bool _bValue)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Red, FString("Toggled gravity, lol"));
}

void IPullable::ResetVelocity()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Red, FString("Reset velocity, lol"));
}

bool IPullable::GetIsPullingRope()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Red, FString("Got pulling rope, lol"));
	return false;
}