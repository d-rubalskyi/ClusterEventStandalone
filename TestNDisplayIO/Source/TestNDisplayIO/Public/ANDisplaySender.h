// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IDisplayCluster.h"
#include "Cluster/IDisplayClusterClusterManager.h"
#include "ANDisplaySender.generated.h"

UCLASS()
class TESTNDISPLAYIO_API ANDisplaySender : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANDisplaySender();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	IDisplayClusterClusterManager* ClusterManager;

	void GenerateSomeClusterEventBinary(FDisplayClusterClusterEventBinary& EventBinary);
	void GenerateSomeClusterEventJson(FDisplayClusterClusterEventJson& EventJson);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
