// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "BlobClass.generated.h"

UCLASS()
class TRACERRACER_API ABlobClass : public APawn
{
	GENERATED_BODY()

public:
	bool Alive;

	// Sets default values for this pawn's properties
	ABlobClass();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void Kill();

	bool IsAlive();

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* OurParticleSystem;
	
};
