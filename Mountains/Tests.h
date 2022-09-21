// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MOUNTAINS_API Tests
{
public:

	static void RunTests();

private:

	static void TestFailed(FString s);
	static void TestPassed(FString s);

	static void TestPerlin();
    static void ReduceTest();
	static void VertexValTest();
	
};
