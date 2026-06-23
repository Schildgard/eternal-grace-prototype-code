// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "InteractableActor_Static.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALGRACE_PROTO_API AInteractableActor_Static : public AInteractableBase
{
	GENERATED_BODY()

protected:
	AInteractableActor_Static();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	UStaticMeshComponent* Mesh;
	
};
