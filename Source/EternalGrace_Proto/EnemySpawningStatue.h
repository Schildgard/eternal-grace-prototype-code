// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor_Static.h"
#include "EnemySpawningStatue.generated.h"

/**
 * 
 */
class AEternalGrace_ProtoCharacter;
class UEnemySpawnComponent;
UCLASS()
class ETERNALGRACE_PROTO_API AEnemySpawningStatue : public AInteractableActor_Static
{
	GENERATED_BODY()

protected:
	AEnemySpawningStatue();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	UEnemySpawnComponent* EnemySpawnComponent;

public:
	void GetInteractedWith_Implementation(AEternalGrace_ProtoCharacter* InteractingPlayer) override;
	void RegisterInteractionRadiusLeave(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex
	)override;
	
};
