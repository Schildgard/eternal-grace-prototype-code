// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_ZoneEntryWidget.h"
#include "Components/TextBlock.h"

void UUI_ZoneEntryWidget::SetZoneName(FName Name)
{
	ZoneName->SetText(FText::FromName(Name));
}
