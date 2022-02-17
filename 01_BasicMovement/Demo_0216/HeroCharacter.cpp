// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AHeroCharacter::AHeroCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate

	GetCharacterMovement()->JumpZVelocity = 600.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f; // The camera follows at this distance behind the character	
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpringArm->TargetArmLength = 500.0f;
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHeroCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHeroCharacter::MoveRight);

	PlayerInputComponent->BindAxis("MouseX", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MouseY", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AHeroCharacter::Attack);
}

void AHeroCharacter::MoveForward(float Value)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AHeroCharacter::MoveRight(float Value)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

bool AHeroCharacter::isRunning()
{
	return GetCharacterMovement()->GetCurrentAcceleration().Size() > 1e-4;
}

void AHeroCharacter::Attack()
{
	PlayAnimMontage(AttackAnim);

	FVector Start = this->GetActorLocation();
	FVector End = this->GetActorLocation() + this->GetActorForwardVector() * 120;

	TArray<AActor*> IngoreActors;
	TArray<FHitResult> HitResult;

	UKismetSystemLibrary::SphereTraceMulti(this->GetWorld(), Start, End, 100, TraceTypeQuery1, true,
		IngoreActors, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::White, FLinearColor::Black, 10);

	for (FHitResult Hit : HitResult)
	{
		if (Hit.Actor != nullptr && Hit.Actor.Get() != nullptr)
		{
			if (Hit.Actor.Get()->ActorHasTag("Box"))
			{
				UPrimitiveComponent* PrimitiveComponent = Hit.GetComponent();
				if (PrimitiveComponent && PrimitiveComponent->IsSimulatingPhysics())
				{
					FVector Direction = Hit.TraceEnd - Hit.TraceStart;
					Direction.Normalize();

					PrimitiveComponent->AddImpulseAtLocation(Direction * 1e5, Hit.ImpactPoint, Hit.BoneName);
				}

				UE_LOG(LogTemp, Warning, TEXT("Hit Box"));
			}

			if (Hit.Actor.Get()->ActorHasTag("Enemy"))
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit Enemy"));
				auto Res = Hit.Actor.Get()->GetComponentsByClass(UHealthComponent::StaticClass());
				for (int i = 0; i < Res.Num(); ++i)
				{
					Cast<UHealthComponent>(Res[i])->ApplyHealthChange(this, -20);
				}
			}
		}
	}
}