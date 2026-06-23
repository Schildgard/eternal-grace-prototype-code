// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "ObjectType.h"
#include "Interactable.h"
#include "EquipmentBase.generated.h"

/**
 * 
 */
class AEternalGrace_ProtoCharacter;
UCLASS()
class ETERNALGRACE_PROTO_API UEquipmentBase : public USkeletalMeshComponent, public IInteractable
{
	GENERATED_BODY()


protected:
	UEquipmentBase();

	UPROPERTY()
	EObjectType ObjectType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TSoftObjectPtr<UTexture2D> Icon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	FName ItemName;

public:
	virtual void GetInteractedWith(AEternalGrace_ProtoCharacter* Interactor);
	FName GetItemName();
	EObjectType GetObjectType();
	TSoftObjectPtr<UTexture2D> GetIcon();
};
