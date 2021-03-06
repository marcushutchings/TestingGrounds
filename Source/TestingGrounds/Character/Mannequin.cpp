// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapons/Gun.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FP_Camera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Arms"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
}

USkeletalMeshComponent * AMannequin::GetMeshToAttachGunTo()
{
	USkeletalMeshComponent* SelectedMesh = GetMesh();

	if (IsPlayerControlled())
	{
		SelectedMesh = Mesh1P;
	}

	return SelectedMesh;
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	
	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	SpawnGun();
	BindInputs();
}

void AMannequin::SpawnGun()
{
	if (!ensure(FP_GunBlueprint)) return;

	FP_Gun = GetWorld()->SpawnActor<AGun>(FP_GunBlueprint);
	if (FP_Gun)
	{
		FP_Gun->AttachToComponent(GetMeshToAttachGunTo(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		FP_Gun->FPAnimInstance = Mesh1P->GetAnimInstance();
		FP_Gun->TPAnimInstance = GetMesh()->GetAnimInstance();
	}
}

void AMannequin::BindInputs()
{
	if (InputComponent)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
	}
}

void AMannequin::PullTrigger()
{
	if (FP_Gun) FP_Gun->Fire();
}


void AMannequin::UnPossessed()
{
	Super::UnPossessed();

	if (FP_Gun)
	{
		FP_Gun->AttachToComponent(GetMeshToAttachGunTo(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

