// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JJH_Corpse.generated.h"

UCLASS()
class RAGDOLLANDGRAB_API AJJH_Corpse : public AActor
{
	GENERATED_BODY()
	
public:	
	AJJH_Corpse();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
