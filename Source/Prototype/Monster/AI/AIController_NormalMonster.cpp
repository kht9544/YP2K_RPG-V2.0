// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/AIController_NormalMonster.h"

AAIController_NormalMonster::AAIController_NormalMonster()
{
    static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/AI/NormalMonster_BB.NormalMonster_BB'"));
    {
        _bb = BB.Object;
    }

    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/NormalMonster_BT.NormalMonster_BT'"));
    {
        _bt = BT.Object;
    }
}

