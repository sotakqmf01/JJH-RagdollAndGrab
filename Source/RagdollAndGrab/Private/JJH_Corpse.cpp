// Fill out your copyright notice in the Description page of Project Settings.

#include "JJH_Corpse.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"

AJJH_Corpse::AJJH_Corpse() :
	bIsRagdoll(false)
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SetReplicateMovement(true);

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBox"));
	RootBox->SetSimulatePhysics(true);
	RootBox->SetCollisionProfileName(TEXT("CorpseRoot"));
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
	SkeletalMeshComp->SetCollisionProfileName(TEXT("CorpseMesh"));
	SkeletalMeshComp->SetIsReplicated(true);
}

void AJJH_Corpse::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AJJH_Corpse, BoneTransform);
}

void AJJH_Corpse::BeginPlay()
{
	Super::BeginPlay();

}

void AJJH_Corpse::Server_RagdollOn_Implementation()
{
	Multicast_RagdollOn();
}

void AJJH_Corpse::Multicast_RagdollOn_Implementation()
{
	if (HasAuthority())
	{
		bIsRagdoll = true;
		RootBox->SetSimulatePhysics(false);
		SkeletalMeshComp->SetSimulatePhysics(true);
		SkeletalMeshComp->SetCollisionProfileName(TEXT("Ragdoll"));

		TWeakObjectPtr<AJJH_Corpse> WeakThis(this);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle,
			[WeakThis]()
			{
				if (WeakThis.IsValid())
				{
					AJJH_Corpse* Corpse = WeakThis.Get();
					Corpse->BoneTransform = Corpse->SkeletalMeshComp->GetSocketTransform("pelvis", RTS_World);
				}
			},
			0.1f,
			true
		);
	}
	else
	{
		bIsRagdoll = true;
		RootBox->SetSimulatePhysics(false);
		SkeletalMeshComp->SetAllBodiesBelowSimulatePhysics("pelvis", true, false);
	}
}

