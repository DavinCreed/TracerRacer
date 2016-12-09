// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class TRACERRACER_API TrackNameTriggerClass
{
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Basic)
	FString TrackName;

	TrackNameTriggerClass();

	~TrackNameTriggerClass();
};
