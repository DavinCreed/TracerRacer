// Fill out your copyright notice in the Description page of Project Settings.

#include "TracerRacer.h"
#include "BlockClass.h"


// Sets default values
ABlockClass::ABlockClass()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Our root component will be a sphere
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(30.0f);
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
	DeathTime = 0.25f;
}

// Called when the game starts or when spawned
void ABlockClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlockClass::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (!Alive) {
		DeathTime -= DeltaTime;
		if (DeathTime <= 0.0f) {
			OurParticleSystem->ToggleActive();
			Destroy();
		}
	}
}

// Called to bind functionality to input
void ABlockClass::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

bool ABlockClass::IsAlive()
{
	return Alive;
}

void ABlockClass::Kill()
{
	Alive = false;
	OurVisibleComponent->SetVisibility(false);
	if (OurParticleSystem && OurParticleSystem->Template) {
		OurParticleSystem->ToggleActive();
	}
}