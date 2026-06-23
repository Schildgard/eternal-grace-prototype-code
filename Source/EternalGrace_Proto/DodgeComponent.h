// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DodgeComponent.generated.h"



UENUM(BlueprintType)
enum class EDodgeDirection : uint8
{
	None UMETA(DisplayName = "None"),
	Dodge_Forward UMETA(DisplayName = "Forward"),
	Dodge_Backward UMETA(DisplayName = "Backward"),
	Dodge_Leftward UMETA(DisplayName = "Leftward"),
	Dodge_Rightward UMETA(DisplayName = "Rightward")


};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDodgeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDodgeComponent();

protected:
	virtual void BeginPlay() override;

	class AEternalGrace_ProtoCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dodge", meta = (AllowPrivateAccess))
	UAnimMontage* DodgeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dodge", meta = (AllowPrivateAccess))
	EDodgeDirection DodgeDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dodge", meta = (AllowPrivateAccess))
	FName DodgeSectionName;


	FOnMontageBlendingOutStarted OnMontageBlendingOutStarted;
	FOnMontageBlendedInEnded OnMontageBlendedInEnded;

	void OnDodgeMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);
	void OnDodgeMontageBlendedInEnded(UAnimMontage* Montage);

	FTimerHandle ResetDodgeDirectionTimerHandle;

	float ResetDodgeDirectionTimeRate;

	void ResetDodgeDirection();


public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Dodge", meta = (AllowPrivateAccess))
	UAudioComponent* DodgeSoundComponent;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SendMovementVector(FVector2D MovementVector);
	void SetDodgeDirection(FVector2D MovementVector);

	void DirectionalDodge(AEternalGrace_ProtoCharacter* Player);

	void ForwardDodge(AEternalGrace_ProtoCharacter* Player);
};
