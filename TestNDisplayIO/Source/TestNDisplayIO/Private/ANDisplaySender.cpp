// Fill out your copyright notice in the Description page of Project Settings.


#include "ANDisplaySender.h"
#include <Cluster/DisplayClusterClusterEvent.h>

// Sets default values
ANDisplaySender::ANDisplaySender()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANDisplaySender::BeginPlay()
{
	Super::BeginPlay();

	ClusterManager = IDisplayCluster::Get().GetClusterMgr();
	
	// Send cluster event with BINARY data to all nodes

	FDisplayClusterClusterEventBinary EventBinary;
	GenerateSomeClusterEventBinary(EventBinary);

	ClusterManager->EmitClusterEventBinary(EventBinary, false);

	// Send cluster event with JSON data to all nodes

	FDisplayClusterClusterEventJson EventJson;
	GenerateSomeClusterEventJson(EventJson);

	ClusterManager->EmitClusterEventJson(EventJson, false);
}

void ANDisplaySender::GenerateSomeClusterEventBinary(FDisplayClusterClusterEventBinary& EventBinary)
{
	EventBinary.EventId = 1234;

	EventBinary.bIsSystemEvent = false;

	EventBinary.EventData = { 42, 146 };
}

void ANDisplaySender::GenerateSomeClusterEventJson(FDisplayClusterClusterEventJson& EventJson)
{
	EventJson.Name = "MyCommand";
	EventJson.Type = "MyType";

	EventJson.bIsSystemEvent = false;

	EventJson.Parameters.Add("FirstParameter", "42");
	EventJson.Parameters.Add("SecondParameter", "146");
}

// Called every frame
void ANDisplaySender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

