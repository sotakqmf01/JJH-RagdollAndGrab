// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JJH_Corpse.generated.h"

class UBoxComponent;

UCLASS()
class RAGDOLLANDGRAB_API AJJH_Corpse : public AActor
{
	GENERATED_BODY()
	
public:	
	AJJH_Corpse();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UBoxComponent> RootBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp;
};
