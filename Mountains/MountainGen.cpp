// Fill out your copyright notice in the Description page of Project Settings.


#include "MountainGen.h"
#include "MountainSection.h"
#include "PerlinNoise.h"



// Sets default values
AMountainGen::AMountainGen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

void AMountainGen::AddChunk(int x, int y)
{
	UE_LOG(LogTemp, Warning, TEXT("Adding Chunk at %d, %d"), x, y);
	int size = AMountainSection::Size * AMountainSection::BlockSize;
	FActorSpawnParameters sp;
	GetWorld()->SpawnActor<AMountainSection>(FVector(float(size * x), float(size * y), 0.0), FRotator(), sp);

}

FVector AMountainGen::GetPlayerLocation() const
{
	APawn* pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (pawn) {
		return pawn->GetActorLocation();
	}
	return FVector();
}

// Called when the game starts or when spawned
void AMountainGen::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMountainGen::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	FVector location = GetPlayerLocation();
	int32 x = location.X / AMountainSection::Size / AMountainSection::BlockSize;
	int32 y = location.Y / AMountainSection::Size / AMountainSection::BlockSize;
	for (int64 i = x - AMountainSection::LoadDist; i <= x + AMountainSection::LoadDist; i++) {
		for (int64 j = y - AMountainSection::LoadDist; j <= y + AMountainSection::LoadDist; j++) {
			int dx = i - x;
			int dy = j - y;
			if (FMath::Sqrt(dx * dx + dy * dy) < AMountainSection::LoadDist) {
				int64 hash = (i & 0x00000000FFFFFFFF) | (j << 32);
				if (!Chunks.Find(hash)) {
					Chunks.Add(hash);
					AddChunk(i, j);
				}
			}
		}
	}
}

