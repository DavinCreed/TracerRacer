// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "TracerSaveClass.generated.h"

/**
 * 
 */
UCLASS()
class TRACERRACER_API UTracerSaveClass : public USaveGame
{
	GENERATED_BODY()
	
public:
	//Default things
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(EditAnywhere, Category = Basic)
	uint32 UserIndex;

	//Totals
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Totals)
	int BitsAmt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Totals)
	int BitsTotal;

	UTracerSaveClass();
};
