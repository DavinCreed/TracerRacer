// Fill out your copyright notice in the Description page of Project Settings.

#include "TracerRacer.h"
#include "GuardClass.h"


// Sets default values
AGuardClass::AGuardClass()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Our root component will be a sphere
	//Get a root to attach things to
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

	//Create a particle system that we can activate or deactivate
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplodeParticles"));
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/Particles/BlockExplode"));
	if (ParticleAsset.Succeeded()) {
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	Alive = true;
}

// Called when the game starts or when spawned
void AGuardClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGuardClass::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AGuardClass::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

bool AGuardClass::IsAlive()
{
	return Alive;
}

void AGuardClass::Kill()
{
	Alive = false;
	Destroy();
}