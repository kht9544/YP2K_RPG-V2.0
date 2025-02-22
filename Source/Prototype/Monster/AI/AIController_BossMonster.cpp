// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/AIController_BossMonster.h"

AAIController_BossMonster::AAIController_BossMonster()
{
    static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/AI/BossMonster_BB.BossMonster_BB'"));
    {
        _bb = BB.Object;
    }

    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/BossMonster_BT.BossMonster_BT'"));
    {
        _bt = BT.Object;
    }
}

