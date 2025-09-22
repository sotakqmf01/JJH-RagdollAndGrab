// Fill out your copyright notice in the Description page of Project Settings.

#include "JJH_Corpse.h"
#include "Components/BoxComponent.h"

AJJH_Corpse::AJJH_Corpse()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SetReplicateMovement(true);

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBox"));
	RootBox->SetSimulatePhysics(true);
	RootBox->SetCollisionProfileName(TEXT("Pawn"));
	RootBox->SetBoxExtent(FVector(50.0f, 50.0f, 90.0f));
	SetRootComponent(RootBox);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(RootBox);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple"));
	if (MeshAsset.Succeeded())
	{
		SkeletalMeshComp->SetSkeletalMesh(MeshAsset.Object);
	}
	SkeletalMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	SkeletalMeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SkeletalMeshComp->SetCollisionProfileName(TEXT("CharacterMesh"));
	SkeletalMeshComp->SetIsReplicated(true);
}

void AJJH_Corpse::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJJH_Corpse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

