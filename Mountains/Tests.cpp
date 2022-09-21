// Fill out your copyright notice in the Description page of Project Settings.


#include "Tests.h"
#include "PerlinNoise.h"

void Tests::RunTests()
{
	UE_LOG(LogTemp, Warning, TEXT("Running Tests..."));
	TestPerlin();
}


void Tests::TestPerlin()
{
	ReduceTest();
	VertexValTest();
	VertexValTest();
	float a = FMath::Fmod(1.7, 1.0);
	float b = FMath::Fmod(0.7, 1.0);
	float c = FMath::Fmod(-0.3, 1.0);
	float d = FMath::Fmod(-1.3, 1.0);
	UE_LOG(LogTemp, Warning, TEXT("FMOD: a: %f, b: %f, c: %f, d: %f"), a, b, c, d);
	PerlinNoise noise(FVector(1.f, 1.f, 1.f ), 1, 2);
	for (float i = -5.f; i < 5.f; i += 0.2f) {
		float val = noise.Sample({ 0, i, 0 });
		FString s;
		for (float j = 0.0; j < val; j += 0.05) {
			s.Append("x");
		}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *s);
	}
	TestFailed(FString("Perlin Noise Test Failed"));
	TestPassed(FString("Perlin Noise Test Succeded"));
}

void Tests::ReduceTest() {
	PerlinNoise p(FVector(1.0, 1.0, 1.0), 1, 0);
	float t1 = p.reduce({ 0, 1 }, {0});
	float t2 = p.reduce({ 0, 1 }, {0.5});
	float t3 = p.reduce({ 0, 1 }, {1});
	float t4 = p.reduce({ 0, 1 , 2, 3 }, { 0 , 0 });
	float t5 = p.reduce({ 0, 1 , 2, 3 }, { 0.25 , 0 });
	float t6 = p.reduce({ 0, 1 , 2, 3 }, { 0.5 , 0 });
	float t7 = p.reduce({ 0, 1 , 2, 3 }, { 0.75 , 0 });
	float t8 = p.reduce({ 0, 1 , 2, 3 }, { 1 , 0 });
	//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f, %f, %f, %f, %f, %f"), t1, t2, t3, t4, t5, t6, t7, t8);
}

void Tests::VertexValTest() {
	PerlinNoise p(FVector(1.0, 1.0, 1.0), 1, 1);
	float f1 = p.getVertexVal({0,0,0});
	float f2 = p.getVertexVal({0,0,1});
	float f3 = p.getVertexVal({0,0,2});
	float f4 = p.getVertexVal({0,0,3});	
	//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f, %f"), f1, f2, f3, f4);
}

void Tests::TestFailed(FString s)
{
	UE_LOG(LogTemp, Error, TEXT("%s"), *s);
}

void Tests::TestPassed(FString s) {
	UE_LOG(LogTemp, Warning, TEXT("%s"), *s);
}
