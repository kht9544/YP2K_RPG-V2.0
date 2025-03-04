// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_JumpToTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UBTTask_JumpToTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_JumpToTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory)override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,float DeltaSeconds)override;

private:
	bool _isJumping= false;
	
};
