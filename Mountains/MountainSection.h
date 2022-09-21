// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PerlinNoise.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MountainSection.generated.h"

UCLASS()
class MOUNTAINS_API AMountainSection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMountainSection();

	class UInstancedStaticMeshComponent* DefaultBlock;
	class UMaterial* DefaultMaterial;
	static constexpr int BlockSize = 100;
	static constexpr int Size = 10;
	static constexpr int MaxHeight = 32;
	static constexpr int MinHeight = -32;
	static constexpr float LoadDist = 5.f; // Blocks
	static std::vector<PerlinNoise> Noises;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector GetPlayerLocation() const;
	void Generate();
	void Generate2();
	void Grow(float x, float y);

};
