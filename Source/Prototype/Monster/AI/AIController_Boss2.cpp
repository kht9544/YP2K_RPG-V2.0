// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/AIController_Boss2.h"

AAIController_Boss2::AAIController_Boss2()
{
    static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/AI/Boss2_BB.Boss2_BB'"));
	{
		_bb = BB.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/Boss2_BT.Boss2_BT'"));
	{
		_bt = BT.Object;
	}
}

