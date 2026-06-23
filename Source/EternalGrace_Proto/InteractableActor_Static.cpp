// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor_Static.h"
#include "Components/SphereComponent.h"

AInteractableActor_Static::AInteractableActor_Static()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	InteractionSphere->SetupAttachment(RootComponent);
}
