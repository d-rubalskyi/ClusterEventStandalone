// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IDisplayCluster.h"
#include "Cluster/DisplayClusterClusterEvent.h"
#include "Cluster/IDisplayClusterClusterManager.h"
#include "ANDisplayListener.generated.h"

class IDisplayClusterClusterEventListener;

UCLASS()
class TESTNDISPLAYIO_API ANDisplayListener: public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANDisplayListener();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	IDisplayClusterClusterManager* ClusterManager;

	FOnClusterEventJsonListener ListenerJsonDelegate;
	FOnClusterEventBinaryListener ListenerBinaryDelegate;

	void OnClusterEventJson(const FDisplayClusterClusterEventJson& Event);
	void OnClusterEventBinary(const FDisplayClusterClusterEventBinary& Event);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
