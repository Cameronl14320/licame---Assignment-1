// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle movement based on our "MoveX" and "MoveY" axes
	{
		if (!CurrentVelocity.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond to crouching
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AMainPlayer::startCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &AMainPlayer::endCrouch);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AMainPlayer::playerJump);
	InputComponent->BindAction("Fall", IE_Pressed, this, &AMainPlayer::playerFall);

	InputComponent->BindAxis("MoveX", this, &AMainPlayer::Move_XAxis);
}

void AMainPlayer::Move_XAxis(float AxisValue)
{
	// Move at 100 units per second forward or backward
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMainPlayer::playerFall()
{
	if (inAir) {
		CurrentVelocity.Z = FMath::Clamp(-1.0f, -1.0f, 1.0f) * 100.0f;
	}
	else {

	}
}


void AMainPlayer::playerJump()
{
	if (!inAir) {
		inAir = true;
		CurrentVelocity.Z = FMath::Clamp(4.0f, -1.0f, 1.0f) * 100.0f;
	}
}

void AMainPlayer::startCrouch()
{
	if (!inAir) {

	}
}

void AMainPlayer::endCrouch()
{
	if (!inAir) {

	}
}
