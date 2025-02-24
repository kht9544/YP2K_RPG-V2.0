// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerStatData.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UPlayerStatData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	int32 Level;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	int32 MaxHp;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	int32 CurHp;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	int32 MaxMp;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	int32 CurMp;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	int32 Str;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	int32 Dex;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	int32 Int;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	int32 Exp;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	int32 NextExp;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	int32 BonusPoint;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	int32 Money;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	float AttackRadius;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	float AttackRange;
};
