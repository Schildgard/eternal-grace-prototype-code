// Fill out your copyright notice in the Description page of Project Settings.


#include "BlendingWidget.h"
#include "Kismet/GameplayStatics.h"

void UBlendingWidget::PlayAnimationSound()
{
	if (AnimationSound)
	{
		UGameplayStatics::PlaySound2D(this, AnimationSound);
	}
}

void UBlendingWidget::BlendOut()
{
	PlayAnimation(BlendOutAnimation);
	
}

void UBlendingWidget::FinishBlendOut()
{
	RemoveFromParent();
}

void UBlendingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//BIND FUNCTION TO DELEGATE
	StartDelegate.BindDynamic(this, &UBlendingWidget::PlayAnimationSound);
	EndDelegate.BindDynamic(this, &UBlendingWidget::BlendOut);
	BlendOutFinished.BindDynamic(this, &UBlendingWidget::FinishBlendOut);
	//BIND DELEGATE TO ANIMATIONSTART
	BindToAnimationStarted(BlendingAnimation, StartDelegate);
	BindToAnimationFinished(BlendingAnimation, EndDelegate);
	BindToAnimationFinished(BlendOutAnimation, BlendOutFinished);
}
