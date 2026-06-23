// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemySpawnComponent.generated.h"

class AEnemy;
class UNiagaraComponent;
class UEnemySelectWidget;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ETERNALGRACE_PROTO_API UEnemySpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEnemySpawnComponent();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta =(AllowPrivateAccess))
	TArray<TSubclassOf<AEnemy>> EnemyList;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	UNiagaraComponent* NiagaraComponent;

	UPROPERTY()
	TSubclassOf<AEnemy> EnemyClassToSpawn;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void SpawnEnemies();
	UFUNCTION()
	void SpawnSkeleton();
	UFUNCTION()
	void SpawnHammerSkeleton();
	UFUNCTION()
	void SpawnSkeletonKnight();



	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta =(AllowPrivteAccess))
	TSubclassOf<UEnemySelectWidget> EnemySelectWidgetClass;

	UPROPERTY()
	UEnemySelectWidget* SelectWidgetInstance;


	void ShowSelectionWidget(APlayerController* OwningController);


};
