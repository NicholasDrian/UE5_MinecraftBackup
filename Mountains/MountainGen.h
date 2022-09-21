// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <unordered_set>
#include "MountainGen.generated.h"

UCLASS()
class MOUNTAINS_API AMountainGen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	TSet<uint64> Chunks;
	AMountainGen();
	void AddChunk(int x, int y);
	FVector GetPlayerLocation() const;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
