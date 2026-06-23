// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemySelectWidget.generated.h"

/**
 * 
 */

class UEnemyDataWidget;
UCLASS()
class ETERNALGRACE_PROTO_API UEnemySelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//void NativeConstruct()override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess))
	UEnemyDataWidget* Enemy01Data;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	UEnemyDataWidget* Enemy02Data;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	UEnemyDataWidget* Enemy03Data;

	
};
