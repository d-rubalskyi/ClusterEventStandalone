// Fill out your copyright notice in the Description page of Project Settings.

#include "ANDisplayListener.h"


// Sets default values
ANDisplayListener::ANDisplayListener()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANDisplayListener::BeginPlay()
{
	Super::BeginPlay();

	ClusterManager = IDisplayCluster::Get().GetClusterMgr();

	if (ClusterManager != nullptr)
	{
		if (!ListenerJsonDelegate.IsBound())
		{
			ListenerJsonDelegate = FOnClusterEventJsonListener::CreateUObject(this, &ANDisplayListener::OnClusterEventJson);
			ClusterManager->AddClusterEventJsonListener(ListenerJsonDelegate);
		}

		if (!ListenerBinaryDelegate.IsBound())
		{
			ListenerBinaryDelegate = FOnClusterEventBinaryListener::CreateUObject(this, &ANDisplayListener::OnClusterEventBinary);
			ClusterManager->AddClusterEventBinaryListener(ListenerBinaryDelegate);
		}
	}
}

void ANDisplayListener::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (ClusterManager != nullptr)
	{
		ClusterManager->RemoveClusterEventJsonListener(ListenerJsonDelegate);
		ClusterManager->RemoveClusterEventBinaryListener(ListenerBinaryDelegate);
	}
}

// Called every frame
void ANDisplayListener::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANDisplayListener::OnClusterEventJson(const FDisplayClusterClusterEventJson& Event)
{
	UE_LOG(LogBlueprint, Display, TEXT("Received command %s of type %s"), *Event.Name, *Event.Type);
}

void ANDisplayListener::OnClusterEventBinary(const FDisplayClusterClusterEventBinary& Event)
{
	UE_LOG(LogBlueprint, Display, TEXT("Received command with ID %i"), Event.EventId);
}
