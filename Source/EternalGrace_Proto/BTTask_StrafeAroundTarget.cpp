// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StrafeAroundTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "CharacterAnimInstanceBase.h"
#include "DrawDebugHelpers.h"

UBTTask_StrafeAroundTarget::UBTTask_StrafeAroundTarget()
{
	bNotifyTick = true;
	StrafeDistance = 200.f;
	MaxStrafeTime = 4.5f;
	StrafeCountDown = MaxStrafeTime;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_StrafeAroundTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Error, TEXT("%s Starts Strafing (Tick Task, Strafing Task)"), *GetFName().ToString())
		//Get References
		AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	AICharacter = Cast<ACharacter>(AIController->GetPawn());
	if (!AICharacter) return EBTNodeResult::Failed;

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	AActor* TargetActor = Cast<AActor>(Blackboard->GetValueAsObject("TargetPlayer"));
	if (!TargetActor) return EBTNodeResult::Failed;

	AnimInstance = Cast<UCharacterAnimInstanceBase>(AICharacter->GetMesh()->GetAnimInstance());
	if (!AnimInstance) return EBTNodeResult::Failed;

	NormalMovespeed = AICharacter->GetCharacterMovement()->MaxWalkSpeed;

	AIController->SetFocus(TargetActor, EAIFocusPriority::Gameplay);
	AICharacter->GetCharacterMovement()->MaxWalkSpeed = 125.f;
	AnimInstance->CurrentActionState = EActionState::Strafing;



	FVector StrafeTargetPosition = CalculateNewStrafeTargetPosition();
	ShowStrafePoint(StrafeTargetPosition, StrafeTargetPosition + FVector(0.0f, 0.0f, 150.0f));

	AIController->MoveToLocation(StrafeTargetPosition, 10.0f);

	return EBTNodeResult::InProgress;
}

void UBTTask_StrafeAroundTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("No AI Controller (Strafing Task)"));
		return;
	}
	if (AnimInstance->CurrentActionState == EActionState::Strafing)
	{
		StrafeCountDown -= DeltaSeconds;
	}

	EPathFollowingStatus::Type MoveStatus = AIController->GetMoveStatus();
	if (StrafeCountDown <= 0.0f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		//if (MoveStatus == EPathFollowingStatus::Idle || MoveStatus == EPathFollowingStatus::Paused)
		if (MoveStatus != EPathFollowingStatus::Moving)
		{
		//	UE_LOG(LogTemp, Error, TEXT("%s finished Strafing ( Strafing Task)"), *GetFName().ToString());
		//	AICharacter->GetCharacterMovement()->MaxWalkSpeed = NormalMovespeed;
		//	OwnerComp.GetBlackboardComponent()->SetValueAsBool("bCanAttack", true);
		////	AnimInstance->CurrentActionState = EActionState::Idle;
		//	StrafeCountDown = MaxStrafeTime;
		}

	}
}

void UBTTask_StrafeAroundTarget::ShowStrafePoint(FVector StartPosition, FVector EndPosition)
{
	DrawDebugLine(GetWorld(), StartPosition, EndPosition, FColor::Green, false, 5.0f);
}

FVector UBTTask_StrafeAroundTarget::CalculateNewStrafeTargetPosition()
{
	//Calculate TargetStrafe Position
	FVector ForwardLocation = AICharacter->GetActorForwardVector() * 25;
	FVector CurrentLocation = AICharacter->GetActorLocation();
	FVector StrafeDirection = FMath::RandBool() ? AICharacter->GetActorRightVector() : AICharacter->GetActorRightVector() * -1;
	FVector SideLocation = ForwardLocation + CurrentLocation + (StrafeDirection * StrafeDistance);

	return SideLocation;

}

void UBTTask_StrafeAroundTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	UE_LOG(LogTemp, Error, TEXT("Task has been Finished!!"));
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	AICharacter->GetCharacterMovement()->MaxWalkSpeed = NormalMovespeed;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("bCanAttack", true);
	AnimInstance->CurrentActionState = EActionState::Idle;
	StrafeCountDown = MaxStrafeTime;

}
