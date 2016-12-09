// Fill out your copyright notice in the Description page of Project Settings.

#include "TracerRacer.h"
#include "RacerClass.h"
#include "TracerSaveClass.h"
#include "BlockClass.h"
#include "RAMClass.h"
#include "BitClass.h"
#include "BlobClass.h"
#include "GuardClass.h"

// Sets default values
ARacerClass::ARacerClass()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup the assets
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<USoundCue> blockCue;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> bitCue;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> ramCue;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> crashCue;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> engineCue;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> gateCue;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> slowCue;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> switchCue;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> nullRefCue;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> debuggingCue;
		FConstructorStatics()
			: bitCue(TEXT("SoundCue'/Game/SFX/BitCue.BitCue'"))
			, blockCue(TEXT("SoundCue'/Game/SFX/BlockCue.BlockCue'"))
			, crashCue(TEXT("SoundCue'/Game/SFX/CrashCue.CrashCue'"))
			, gateCue(TEXT("SoundCue'/Game/SFX/GateCue.GateCue'"))
			, ramCue(TEXT("SoundCue'/Game/SFX/RAMCue.RAMCue'"))
			, slowCue(TEXT("SoundCue'/Game/SFX/SlowCue.SlowCue'"))
			, switchCue(TEXT("SoundCue'/Game/SFX/SwitchCue.SwitchCue'"))
			, engineCue(TEXT("SoundCue'/Game/SFX/EngineCue.EngineCue'"))
			, nullRefCue(TEXT("SoundCue'/Game/BGM/NullReference_Cue.NullReference_Cue'"))
			, debuggingCue(TEXT("SoundCue'/Game/BGM/Debugging_Cue.Debugging_Cue'"))
		{
		}
	};

	static FConstructorStatics ConstructorStatics;

	//Set this pawn up to be controlled by input
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Get a root to attach things to
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Create a camera
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	//Attach the things to the root
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-32.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);

	//Collision class
	BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseCollisionComponent"));
	BaseCollisionComponent->AttachTo(RootComponent);
	BaseCollisionComponent->SetSphereRadius(50.0f);

	//Sounds
	//Setup the bit sound
	USoundCue* bitSoundCue = ConstructorStatics.bitCue.Get();
	BitSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BitSoundComponent"));
	BitSoundComponent->bAutoActivate = false;
	BitSoundComponent->SetupAttachment(RootComponent);
	if (bitSoundCue->IsValidLowLevelFast()) {
		BitSoundComponent->SetSound(bitSoundCue);
	}

	//Setup the block sound
	USoundCue* blockSoundCue = ConstructorStatics.blockCue.Get();
	BlockSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BlockSoundComponent"));
	BlockSoundComponent->bAutoActivate = false;
	BlockSoundComponent->SetupAttachment(RootComponent);
	if (blockSoundCue->IsValidLowLevelFast()) {
		BlockSoundComponent->SetSound(blockSoundCue);
	}

	//Setup the crash sound
	USoundCue* crashSoundCue = ConstructorStatics.crashCue.Get();
	CrashSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("CrashSoundComponent"));
	CrashSoundComponent->bAutoActivate = false;
	CrashSoundComponent->SetupAttachment(RootComponent);
	if (crashSoundCue->IsValidLowLevelFast()) {
		CrashSoundComponent->SetSound(crashSoundCue);
	}

	//Setup the gate sound
	USoundCue* gateSoundCue = ConstructorStatics.gateCue.Get();
	GateSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("GateSoundComponent"));
	GateSoundComponent->bAutoActivate = false;
	GateSoundComponent->SetupAttachment(RootComponent);
	if (gateSoundCue->IsValidLowLevelFast()) {
		GateSoundComponent->SetSound(gateSoundCue);
	}

	//Setup the RAM sound
	USoundCue* ramSoundCue = ConstructorStatics.ramCue.Get();
	RAMSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("RAMSoundComponent"));
	RAMSoundComponent->bAutoActivate = false;
	RAMSoundComponent->SetupAttachment(RootComponent);
	if (ramSoundCue->IsValidLowLevelFast()) {
		RAMSoundComponent->SetSound(ramSoundCue);
	}

	//Setup the slow sound
	USoundCue* slowSoundCue = ConstructorStatics.slowCue.Get();
	SlowSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SlowSoundComponent"));
	SlowSoundComponent->bAutoActivate = false;
	SlowSoundComponent->SetupAttachment(RootComponent);
	if (slowSoundCue->IsValidLowLevelFast()) {
		SlowSoundComponent->SetSound(slowSoundCue);
	}

	//Setup the switch sound
	USoundCue* switchSoundCue = ConstructorStatics.switchCue.Get();
	SwitchSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SwitchSoundComponent"));
	SwitchSoundComponent->bAutoActivate = false;
	SwitchSoundComponent->SetupAttachment(RootComponent);
	if (switchSoundCue->IsValidLowLevelFast()) {
		SwitchSoundComponent->SetSound(switchSoundCue);
	}

	//Setup the engine sound
	USoundCue* engineSoundCue = ConstructorStatics.engineCue.Get();
	EngineSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("EngineSoundComponent"));
	EngineSoundComponent->SetupAttachment(RootComponent);
	if (engineSoundCue->IsValidLowLevelFast()) {
		EngineSoundComponent->SetSound(engineSoundCue);
	}

	//Create a particle system that we can activate or deactivate
	PrtExplode = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplodeParticles"));
	PrtExplode->SetupAttachment(RootComponent);
	PrtExplode->bAutoActivate = false;
	PrtExplode->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PrtExplodeAsset(TEXT("/Game/Particles/Explode"));
	if (PrtExplodeAsset.Succeeded()) {
		PrtExplode->SetTemplate(PrtExplodeAsset.Object);
	}

	//Create a particle system that we can activate or deactivate
	PrtFinish = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FinishParticles"));
	PrtFinish->SetupAttachment(RootComponent);
	PrtFinish->bAutoActivate = false;
	PrtFinish->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PrtFinishAsset(TEXT("/Game/Particles/ExplodeFinish"));
	if (PrtFinishAsset.Succeeded()) {
		PrtFinish->SetTemplate(PrtFinishAsset.Object);
	}

	//Default values
	Hits = HitsMax = 3;
	IsAlive = true;
	InPlay = false;
	SpeedMax = 4000;
	Bits = 0;
	Gates = 0;
	engineGoing = true;
	EngineSoundComponent->Stop();
}

// Called when the game starts or when spawned
void ARacerClass::BeginPlay()
{
	Super::BeginPlay();
	InPlay = true;
	EngineSoundComponent->Stop();
}

// Called every frame
void ARacerClass::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (!InPlay) return;
	if (IsAlive) CollisionCheck();
	float laneWidth = 100.0f;

	if (Hits > 0 && CurrentVelocity.X < (float)SpeedMax) {
		CurrentVelocity.X += 500.0f * DeltaTime;

		if (CurrentVelocity.X > (float)SpeedMax) CurrentVelocity.X = (float)SpeedMax;
		Speed = (int)CurrentVelocity.X;
	}

	if (!CurrentVelocity.IsZero()) {
		FVector curLoc = GetActorLocation();
		FVector NewLocation = curLoc + (CurrentVelocity * DeltaTime);
		if (CurrentVelocity.Y < 0.0f) {
			if (curLoc.Y < (float)CurrentLane * laneWidth) {
				CurrentVelocity.Y = 0.0f;
				NewLocation.Y = (float)CurrentLane * laneWidth;
			}
		}
		else if (CurrentVelocity.Y > 0.0f) {
			if (curLoc.Y >(float)CurrentLane * laneWidth) {
				CurrentVelocity.Y = 0.0f;
				NewLocation.Y = (float)CurrentLane * laneWidth;
			}
		}
		else {
			if (curLoc.Y > -0.01f && curLoc.Y < 0.01f) {
				CurrentVelocity.Y = 0.0f;
				NewLocation.Y = 0.0f;
			}
		}
		SetActorLocation(NewLocation);
	}

	if (Gates >= 4) {
		engineGoing = false;
		CurrentVelocity.X = 0.0f;
		InPlay = false;
		if (PrtFinish && PrtFinish->Template) {
			PrtFinish->ToggleActive();
		}
	}

	//Keep track of the engine
	if (CurrentVelocity.X == 0.0f && engineGoing) {
		EngineSoundComponent->Stop();
		engineGoing = false;
	}
	else if (CurrentVelocity.X > 0.0f && !engineGoing) {
		//EngineSoundComponent->Play();
		engineGoing = true;
	}

	if (engineGoing) {
		EngineSoundComponent->SetPitchMultiplier((CurrentVelocity.X) + 10.0f);
	}
}

void ARacerClass::CollisionCheck()
{
	TArray<AActor*> HitActors;
	BaseCollisionComponent->GetOverlappingActors(HitActors);

	for (int32 i = 0; i < HitActors.Num(); ++i) {
		//Check for block collisions
		ABlockClass* const TestBlock = Cast<ABlockClass>(HitActors[i]);
		if (TestBlock && TestBlock->IsAlive()) {
			//Explode
			TestBlock->Kill();
			Hits--;
			if (CurrentVelocity.X >= 2000.0f) CurrentVelocity.X -= 2000.0f;
			else CurrentVelocity.X = 0.0f;
			BlockSoundComponent->Play();
			if (Hits <= 0) {
				Kill();
			}
		}

		//Check for blob collisions
		ABlobClass* const TestBlob = Cast<ABlobClass>(HitActors[i]);
		if (TestBlob && TestBlob->IsAlive()) {
			//Slow FX
			if (CurrentVelocity.X > 1000.0f) CurrentVelocity.X = 1000.0f;
			SlowSoundComponent->Play();
		}

		//Check for RAM collisions
		ARAMClass* const TestRAM = Cast<ARAMClass>(HitActors[i]);
		if (TestRAM && TestRAM->IsAlive()) {
			//Explode
			TestRAM->Kill();
			if (RAMs < 4) RAMs++;
			RAMSoundComponent->Play();
		}

		//Check for bit collisions
		ABitClass* const TestBit = Cast<ABitClass>(HitActors[i]);
		if (TestBit && TestBit->IsAlive()) {
			//Explode
			TestBit->Kill();
			Bits++;
			BitSoundComponent->Play();
		}

		//Check for guard collisions
		AGuardClass* const TestGuard = Cast<AGuardClass>(HitActors[i]);
		if (TestGuard && TestGuard->IsAlive()) {
			if (RAMs >= 4) {
				//Explode
				TestGuard->Kill();
				RAMs = 0;
				Gates++;
				GateSoundComponent->Play();
			}
			else {
				Kill();
			}
		}
	}
}


// Called to bind functionality to input
void ARacerClass::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAction(TEXT("LaneLeft"), IE_Pressed, this, &ARacerClass::Move_LaneLeft);
	InputComponent->BindAction(TEXT("LaneRight"), IE_Pressed, this, &ARacerClass::Move_LaneRight);
}

void ARacerClass::Move_LaneLeft()
{
	if (CurrentLane <= -1) return;
	CurrentLane--;
	CurrentVelocity.Y = -1000.0f;
	SwitchSoundComponent->Play();
}

void ARacerClass::Move_LaneRight()
{
	if (CurrentLane >= 1) return;
	CurrentLane++;
	CurrentVelocity.Y = 1000.0f;
	SwitchSoundComponent->Play();
}

int ARacerClass::CurrentHits_Implementation()
{
	return Hits;
}

int ARacerClass::CurrentBits_Implementation()
{
	return Bits;
}

int ARacerClass::CurrentRAMs_Implementation()
{
	return RAMs;
}

void ARacerClass::Kill()
{
	Hits = 0;
	IsAlive = false;
	CurrentVelocity.X = 0.0f;
	CrashSoundComponent->Play();
	EngineSoundComponent->Stop();
	if (PrtExplode && PrtExplode->Template) {
		PrtExplode->ToggleActive();
	}
}