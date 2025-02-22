// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAIController();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	void RandMove();

protected:
	UPROPERTY()
	class UBlackboardData* _bb;

	UPROPERTY()
	class UBehaviorTree* _bt;

	static const FName TargetKey;

};
