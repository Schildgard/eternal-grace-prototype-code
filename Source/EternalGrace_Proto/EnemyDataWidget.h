// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonWidget.h"
#include "EnemyDataWidget.generated.h"

/**
 * 
 */
class AEnemy;
class UTextBlock;
UCLASS()
class ETERNALGRACE_PROTO_API UEnemyDataWidget : public UButtonWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	FName EnemyName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TSubclassOf<AEnemy> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ButtonText;
	
};
