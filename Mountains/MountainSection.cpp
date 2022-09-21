// Fill out your copyright notice in the Description page of Project Settings.


#include "MountainSection.h"
#include "MountainGen.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "GameFramework/GameModeBase.h"


std::vector<PerlinNoise> AMountainSection::Noises = {
	PerlinNoise(FVector(40, 40, 40) * BlockSize, 1.0f, time(0)),
	PerlinNoise(FVector(10, 10, 10) * BlockSize, 0.25f, time(0))
};




// Sets default values
AMountainSection::AMountainSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultBlock = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Default Block"));
	DefaultBlock->RegisterComponent();
	ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultBlockInstance(TEXT("/Game/Mine/100Cube.100Cube"));
	if (DefaultBlockInstance.Succeeded()) 
		DefaultBlock->SetStaticMesh(DefaultBlockInstance.Object);
	RootComponent = DefaultBlock;
	

	DefaultMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Default Material"));
	ConstructorHelpers::FObjectFinder<UMaterial> DefaultMaterialInstance(TEXT("/Engine/EngineMaterials/DefaultMaterial.DefaultMaterial"));
	if (DefaultMaterialInstance.Succeeded()) DefaultBlock->SetMaterial(0, DefaultMaterialInstance.Object);

}


// Called when the game starts or when spawned
void AMountainSection::BeginPlay()
{
	Super::BeginPlay();
	DefaultBlock->AddInstance(FTransform(), true);
	Generate();
}


void AMountainSection::Generate() {
	bool isAir[Size + 2][Size + 2][MaxHeight - MinHeight + 2] = { { {false} } };
	for (int i = -1; i <= Size; i++) {
		for (int j = -1; j <= Size; j++) {
			for (int k = MinHeight - 1; k <= MaxHeight; k++) {
				FVector location = GetActorLocation() + FVector(i, j, k) * BlockSize;
				float sample = float(k) / 32.f;
				for (PerlinNoise p : Noises) {
					sample += p.Sample({ float(location.X), float(location.Y), float(location.Z) });
				}
				isAir[i + 1][j + 1][k - MinHeight + 1] = sample > 0.5;
			}
		}
	}
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			for (int k = MinHeight; k < MaxHeight; k++) {
				int x = i + 1, y = j + 1, z = k - MinHeight + 1;
				if (!isAir[x][y][z] &&
					(isAir[x + 1][y][z] ||
				   	isAir[x - 1][y][z] ||
					isAir[x][y + 1][z] ||
					isAir[x][y - 1][z] ||
					isAir[x][y][z + 1] ||
					isAir[x][y][z - 1])) {
					FTransform t = GetActorTransform();
					t.AddToTranslation(FVector(i, j, k) * BlockSize);
					DefaultBlock->AddInstance(t, true);
				}
			}
		}
	}
}

// Called every frame
void AMountainSection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector PlayerLocation = GetPlayerLocation();
	FVector SectionLocation = GetActorLocation();
	PlayerLocation.Z = 0;
	SectionLocation.Z = 0;
	if (FVector::Distance(PlayerLocation, SectionLocation) > LoadDist * Size * BlockSize) {
		UE_LOG(LogTemp, Warning, TEXT("Chunk Destroyed"));
		Destroy();
	}
}

FVector AMountainSection::GetPlayerLocation() const {
	APawn* pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (pawn) return pawn->GetActorLocation();
	return FVector();
}

