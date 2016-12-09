// Fill out your copyright notice in the Description page of Project Settings.

#include "TracerRacer.h"
#include "BlobClass.h"


// Sets default values
ABlobClass::ABlobClass()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Our root component will be a sphere
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(20.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Block"));

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

	//Create a particle system that we can activate or deactivate
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplodeParticles"));
	OurParticleSystem->SetupAttachment(SphereComponent);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/Particles/BlockExplode"));
	if (ParticleAsset.Succeeded()) {
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	Alive = true;
}

// Called when the game starts or when spawned
void ABlobClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlobClass::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ABlobClass::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

bool ABlobClass::IsAlive()
{
	return Alive;
}

void ABlobClass::Kill()
{
	Alive = false;
	Destroy();
}