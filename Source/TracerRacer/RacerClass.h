// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TracerSaveClass.h"
#include "GameFramework/Pawn.h"
#include "RacerClass.generated.h"

UCLASS()
class TRACERRACER_API ARacerClass : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	int Hits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	int HitsMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	int RAMs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	int Bits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	int Gates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	int Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Upgrade)
	int SpeedMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Upgrade)
	FString CurrentTrack;

	bool IsAlive;
	bool InPlay;

	// Sets default values for this pawn's properties
	ARacerClass();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Check collisions
	void CollisionCheck();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere)
	class USphereComponent* BaseCollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	UCameraComponent* OurCamera;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* PrtExplode;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* PrtFinish;

	//SFX
	UAudioComponent* BitSoundComponent;
	UAudioComponent* BlockSoundComponent;
	UAudioComponent* CrashSoundComponent;
	UAudioComponent* GateSoundComponent;
	UAudioComponent* RAMSoundComponent;
	UAudioComponent* SlowSoundComponent;
	UAudioComponent* SwitchSoundComponent;
	bool engineGoing;
	UAudioComponent* EngineSoundComponent;

	//Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Music)
	UAudioComponent* MusicNullReference;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Music)
	UAudioComponent* MusicDebugging;
	
	UTracerSaveClass* SaveGameInstance;

	//Input functions
	void Move_LaneLeft();
	void Move_LaneRight();

	//Input variables
	FVector CurrentVelocity;
	int CurrentLane;

	//Variables
	UFUNCTION(BlueprintNativeEvent)
	int CurrentHits();
	virtual int CurrentHits_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	int CurrentBits();
	virtual int CurrentBits_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	int CurrentRAMs();
	virtual int CurrentRAMs_Implementation();

	//Player managment functions
	void Kill();
};
