// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BaseAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ABaseAIController::ABaseAIController()
{
    
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    UBlackboardComponent *blackboardComponent = Blackboard;
    if (UseBlackboard(_bb, blackboardComponent))
    {
        if (RunBehaviorTree(_bt))
        {
            blackboardComponent->SetValueAsVector(FName(TEXT("FixedPos")),InPawn->GetActorLocation());
        }
    }
}

void ABaseAIController::OnUnPossess()
{
    Super::OnUnPossess();
}

void ABaseAIController::RandMove()
{
    auto currentPawn = GetPawn();

	if (!currentPawn->IsValidLowLevel())
		return;

	UNavigationSystemV1* NaviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NaviSystem == nullptr)
		return;

	FNavLocation randLocation;

	if (NaviSystem->GetRandomPointInNavigableRadius(currentPawn->GetActorLocation(), 500.f, randLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, randLocation);
	}
}
