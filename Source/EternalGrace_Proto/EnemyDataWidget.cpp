// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDataWidget.h"
#include "Enemy.h"
#include "Components/TextBlock.h"

void UEnemyDataWidget::NativeConstruct()
{
	ButtonText->SetText(FText::FromName(EnemyName));
}
