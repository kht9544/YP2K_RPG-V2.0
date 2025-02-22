// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/AIController_Epic.h"



AAIController_Epic::AAIController_Epic()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/AI/EpicMonster_BB.EpicMonster_BB'"));
	{
		_bb = BB.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/EpicMonster_BT.EpicMonster_BT'"));
	{
		_bt = BT.Object;
	}
}

