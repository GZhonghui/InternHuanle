// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerCharacter.h"

// Sets default values
AMainPlayerCharacter::AMainPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);

	// Create a follow camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpringArm->TargetArmLength = 480;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera->SetRelativeLocation(FVector(-80, 0, 840));
	Camera->SetRelativeRotation(FRotator(-60, 0, 0));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	Attacking = false;

	WhichAttackState = 0;

	AttackNumberValue = 0;
	AttackTimeValue = 0;

	LastAttack = FDateTime::Now();
}

// Called every frame
void AMainPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto Now = FDateTime::Now();
	auto Passed = (Now - LastAttack).GetTotalMilliseconds();

	if (Passed >= AttackNumberTimeMax)
	{
		AttackNumberValue = 0;
		AttackTimeValue = 0;

		WhichAttackState = 0;
	}
	else
	{
		AttackTimeValue = 1.0f - (float)(Passed / AttackNumberTimeMax);
	}
}

// Called to bind functionality to input
void AMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainPlayerCharacter::Attack);
}

void AMainPlayerCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMainPlayerCharacter::MoveForward(float Value)
{
	if (Attacking) return;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AMainPlayerCharacter::MoveRight(float Value)
{
	if (Attacking) return;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AMainPlayerCharacter::Attack()
{
	if (Attacking) return;

	if (AttackAnims.Num())
	{
		if (WhichAttackState >= AttackAnims.Num()) WhichAttackState = 0;

		PlayAnimMontage(AttackAnims[WhichAttackState]);
		WhichAttackState += 1;
	}

	FVector Start = this->GetActorLocation();
	FVector End = this->GetActorLocation() + this->GetActorForwardVector() * 160;

	TArray<AActor*> IngoreActors;
	TArray<FHitResult> HitResult;

	UKismetSystemLibrary::SphereTraceMulti(this->GetWorld(), Start, End, 100, TraceTypeQuery1, true,
		IngoreActors, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::White, FLinearColor::Black, 10);
}

void AMainPlayerCharacter::AttackPoint()
{
	// Calc Collision

	LastAttack = FDateTime::Now();
	AttackNumberValue = AttackNumberValue < 99 ? AttackNumberValue + 1 : 99;
}

float AMainPlayerCharacter::GetSpeed()
{
	return GetCharacterMovement()->GetCurrentAcceleration().Size();
}