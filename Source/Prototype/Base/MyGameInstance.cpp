// Fill out your copyright notice in the Description page of Project Settings.
#include "Base/MyGameInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/StatComponent.h"
#include "Component/InventoryComponent.h"
#include "PlayerStatData.h"
#include "Player/MyPlayer.h"
#include "Item/BaseItem.h"
#include "Item/Equip/EquipItem.h"
#include "Item/Consumes/ConsumeItem.h"
#include "../UI/InventoryWidget.h"
#include "../Item/Equip/EquipItem.h"
#include "../Component/InventoryComponent.h"
#include "Base/Managers/UIManager.h"
#include "Base/Managers/SoundManager.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> StatData(TEXT("/Script/Engine.DataTable'/Game/Data/StatDataTable.StatDataTable'"));

	if (StatData.Succeeded())
	{
		_statTable = StatData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> EpicStatData(TEXT("/Script/Engine.DataTable'/Game/Data/EpicMonsterDataTable.EpicMonsterDataTable'"));

	if (EpicStatData.Succeeded())
	{
		_EpicstatTable = EpicStatData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterStatData(TEXT("/Script/Engine.DataTable'/Game/Data/NormalMonsterDataTable.NormalMonsterDataTable'"));

	if (MonsterStatData.Succeeded())
	{
		_MonsterstatTable = MonsterStatData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> BossStatData(TEXT("/Script/Engine.DataTable'/Game/Data/BossMonsterDataTable.BossMonsterDataTable'"));

	if (BossStatData.Succeeded())
	{
		_BossstatTable = BossStatData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> ConsumItemData(TEXT("/Script/Engine.DataTable'/Game/Data/Item/ConsumeItem.ConsumeItem'"));

	if (ConsumItemData.Succeeded())
	{
		_ConsItemTable = ConsumItemData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> EquipItemData(TEXT("/Script/Engine.DataTable'/Game/Data/Item/Equipitem.Equipitem'"));

	if (EquipItemData.Succeeded())
	{
		_EquipItemTable = EquipItemData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DragonStat(TEXT("/Script/Engine.DataTable'/Game/Data/DragonStatDataTable.DragonStatDataTable'"));

	if (DragonStat.Succeeded())
	{
		_DragonStatTable = DragonStat.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> shopList1(TEXT("/Script/Engine.DataTable'/Game/Data/Postion_ShopKeeper.Postion_ShopKeeper'"));
	if (shopList1.Succeeded())
	{
		_ShopLists.Add(shopList1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> shopList2(TEXT("/Script/Engine.DataTable'/Game/Data/BasicEquip_ShopKeeper.BasicEquip_ShopKeeper'"));
	if (shopList2.Succeeded())
	{
		_ShopLists.Add(shopList2.Object);
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> shopList3(TEXT("/Script/Engine.DataTable'/Game/Data/ShinyEquip_ShopKeeper.ShinyEquip_ShopKeeper'"));
	if (shopList3.Succeeded())
	{
		_ShopLists.Add(shopList3.Object);
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> shopList4(TEXT("/Script/Engine.DataTable'/Game/Data/ShadowEquip_ShopKeeper.ShadowEquip_ShopKeeper'"));
	if (shopList4.Succeeded())
	{
		_ShopLists.Add(shopList4.Object);
	}
	SavedSkeletalMeshes.SetNum(6);
}


void UMyGameInstance::SavePlayerStats(class UStatComponent *StatComponent)
{
	if (StatComponent && SavedPlayerStats)
	{
		SavedPlayerStats->Level = StatComponent->GetLevel();
		SavedPlayerStats->MaxHp = StatComponent->GetMaxHp();
		SavedPlayerStats->CurHp = StatComponent->GetCurHp();
		SavedPlayerStats->MaxMp = StatComponent->GetMaxMp();
		SavedPlayerStats->CurMp = StatComponent->GetCurMp();
		SavedPlayerStats->Str = StatComponent->GetStr();
		SavedPlayerStats->Dex = StatComponent->GetDex();
		SavedPlayerStats->Int = StatComponent->GetInt();
		SavedPlayerStats->Exp = StatComponent->GetExp();
		SavedPlayerStats->NextExp = StatComponent->GetNextExp();
		SavedPlayerStats->BonusPoint = StatComponent->GetBonusPoint();
		SavedPlayerStats->AttackRadius = StatComponent->GetAttackRadius();
		SavedPlayerStats->AttackRange = StatComponent->GetAttackRange();

		  	UE_LOG(LogTemp, Warning, TEXT("save: level: %d, hhP: %d, HP: %d, mMP: %d, MP: %d, sgtr: %d, d: %d, i: %d, e: %d, e: %d, b: %d, r: %f, r: %f"),
            SavedPlayerStats->Level,
            SavedPlayerStats->MaxHp,
            SavedPlayerStats->CurHp,
            SavedPlayerStats->MaxMp,
            SavedPlayerStats->CurMp,
            SavedPlayerStats->Str,
            SavedPlayerStats->Dex,
            SavedPlayerStats->Int,
            SavedPlayerStats->Exp,
            SavedPlayerStats->NextExp,
            SavedPlayerStats->BonusPoint,
            SavedPlayerStats->AttackRange,
            SavedPlayerStats->AttackRadius);
	}
}

void UMyGameInstance::LoadPlayerStats(class UStatComponent *StatComponent)
{
	if (StatComponent && SavedPlayerStats)
	{
		StatComponent->SetLevel(SavedPlayerStats->Level);
		StatComponent->SetMaxHp(SavedPlayerStats->MaxHp);
		StatComponent->SetHp(SavedPlayerStats->CurHp);
		StatComponent->SetMaxMp(SavedPlayerStats->MaxMp);
		StatComponent->SetMp(SavedPlayerStats->CurMp);
		StatComponent->SetStr(SavedPlayerStats->Str);
		StatComponent->SetDex(SavedPlayerStats->Dex);
		StatComponent->SetInt(SavedPlayerStats->Int);
		StatComponent->SetExp(SavedPlayerStats->Exp);
		StatComponent->SetNextExp(SavedPlayerStats->NextExp);
		StatComponent->SetBonusPoint(SavedPlayerStats->BonusPoint);
		StatComponent->SetAttackRange(SavedPlayerStats->AttackRange);
		StatComponent->SetAttackRadius(SavedPlayerStats->AttackRadius);

		  UE_LOG(LogTemp, Warning, TEXT("load: level: %d, hhP: %d, HP: %d, mMP: %d, MP: %d, sgtr: %d, d: %d, i: %d, e: %d, e: %d, b: %d, r: %f, r: %f"),
            SavedPlayerStats->Level,
            SavedPlayerStats->MaxHp,
            SavedPlayerStats->CurHp,
            SavedPlayerStats->MaxMp,
            SavedPlayerStats->CurMp,
            SavedPlayerStats->Str,
            SavedPlayerStats->Dex,
            SavedPlayerStats->Int,
            SavedPlayerStats->Exp,
            SavedPlayerStats->NextExp,
            SavedPlayerStats->BonusPoint,
            SavedPlayerStats->AttackRange,
            SavedPlayerStats->AttackRadius);

		StatComponent->UpdateUI();
	}
}

void UMyGameInstance::SaveInventory(class UInventoryComponent *InventoryComponent)
{
	 if (InventoryComponent)
    {
        SavedInventoryCodes.Empty();
        SavedEquipCodes.Empty();

        TArray<ABaseItem *> Items = InventoryComponent->GetItemSlots();
        for (int32 i = 0; i < Items.Num(); ++i)
        {
            ABaseItem* Item = Items[i];
            if (Item)
            {
                SavedInventoryCodes.Add(Item->GetCode());
            }
            else
			{
                SavedInventoryCodes.Add(-1);
            }
        }

        TMap<FString, AEquipItem *> EquipItems = InventoryComponent->GetEquipSlots();
        for (auto &Elem : EquipItems)
        {
            if (Elem.Value)
            {
                SavedEquipCodes.Add(Elem.Key, Elem.Value->GetCode());
            }
            else
            {
                SavedEquipCodes.Add(Elem.Key, -1);
            }
        }

       // SavedPlayerStats->Money = InventoryComponent->GetMoney();
    }
}

void UMyGameInstance::LoadInventory(class UInventoryComponent *InventoryComponent)
{
	 if (InventoryComponent)
    {
        InventoryComponent->InitSlot();

        for (int32 i = 0; i < SavedInventoryCodes.Num(); ++i)
        {
            int32 Code = SavedInventoryCodes[i];
            if (Code != -1)
            {
                ABaseItem* NewItem = nullptr;
                if (GetConsumeItemData(Code))
                {
                    NewItem = GetWorld()->SpawnActor<AConsumeItem>(AConsumeItem::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
                }
                else if (GetEquipItemData(Code))
                {
                    NewItem = GetWorld()->SpawnActor<AEquipItem>(AEquipItem::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
                }
                
                if (NewItem)
                {
                    NewItem->SetItemWithCode(Code);
                    InventoryComponent->AddItem(i, NewItem);
                }
            }
        }

        for (auto &Elem : SavedEquipCodes)
        {
            int32 Code = Elem.Value;
            if (Code != -1)
            {
                AEquipItem* NewEquip = GetWorld()->SpawnActor<AEquipItem>(AEquipItem::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
                if (NewEquip)
                {
                    NewEquip->SetItemWithCode(Code);
                    InventoryComponent->AddItemToEquip(Elem.Key, NewEquip);
                }
            }
        }
        //InventoryComponent->AddMoney(SavedPlayerStats->Money);
    }
}

void UMyGameInstance::SavePlayerSkeletal(class AMyPlayer *player)
{
	if (player)
	{
		SavedSkeletalMeshes[0] = Cast<USkeletalMesh>(player->GetMesh()->GetSkinnedAsset());
		SavedSkeletalMeshes[1] = Cast<USkeletalMesh>(player->GetLowerBodyMesh()->GetSkinnedAsset());
		SavedSkeletalMeshes[2] = Cast<USkeletalMesh>(player->GetShoulderBodyMesh()->GetSkinnedAsset());
		SavedSkeletalMeshes[3] = Cast<USkeletalMesh>(player->GetSwordBodyMesh()->GetSkinnedAsset());
		SavedSkeletalMeshes[4] = Cast<USkeletalMesh>(player->GetShieldBodyMesh()->GetSkinnedAsset());
	}
}

void UMyGameInstance::LoadPlayerSkeletal(class AMyPlayer *player)
{
	if (player && SavedSkeletalMeshes.Num() > 0)
	{
		player->GetMesh()->SetSkeletalMesh(SavedSkeletalMeshes[0]);
		player->GetLowerBodyMesh()->SetSkeletalMesh(SavedSkeletalMeshes[1]);
		player->GetShoulderBodyMesh()->SetSkeletalMesh(SavedSkeletalMeshes[2]);
		player->GetSwordBodyMesh()->SetSkeletalMesh(SavedSkeletalMeshes[3]);
		player->GetShieldBodyMesh()->SetSkeletalMesh(SavedSkeletalMeshes[4]);
	}
}

void UMyGameInstance::SavePlayer(class AMyPlayer *player)
{
	SavePlayerStats(player->GetStatComponent());
	SaveInventory(player->GetInventory());
	SavePlayerSkeletal(player);
}

TArray<ABaseItem *> UMyGameInstance::GetInvenItemList()
{
	return UIManager->GetInventoryUI()->GetInvenContents();
}

void UMyGameInstance::Init()
{
	Super::Init();

	InitializeManagers();
	if (!SavedPlayerStats)
    {
        SavedPlayerStats = NewObject<UPlayerStatData>(this, UPlayerStatData::StaticClass());
    }
}

void UMyGameInstance::InitializeManagers()
{
	FActorSpawnParameters params;
	params.Name = TEXT("UIManager");
	_UIManager = GetWorld()->SpawnActor<AUIManager>(FVector::ZeroVector, FRotator::ZeroRotator, params);

	FActorSpawnParameters soundParams;
	soundParams.Name = TEXT("SoundManager");
	_soundManager = GetWorld()->SpawnActor<ASoundManager>(FVector::ZeroVector, FRotator::ZeroRotator, soundParams);

	FActorSpawnParameters effectParams;
	effectParams.Name = TEXT("EffectManager");
	_effectManager = GetWorld()->SpawnActor<AEffectManager>(FVector::ZeroVector, FRotator::ZeroRotator, effectParams);
}

FMyStatData *UMyGameInstance::GetStatDataByLevel(int level)
{
	auto statData = _statTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return statData;
}

FMyStatData *UMyGameInstance::GetMonsterDataByLevel(int level)
{
	auto MonsterData = _MonsterstatTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return MonsterData;
}

FMyStatData *UMyGameInstance::GetEpicDataByLevel(int level)
{
	auto EpicStatData = _EpicstatTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return EpicStatData;
}

FMyStatData *UMyGameInstance::GetBossDataByLevel(int level)
{
	auto BossStatData = _BossstatTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return BossStatData;
}

FMyStatData *UMyGameInstance::GetDragonDataByLevel(int level)
{
	auto DragonStatData = _DragonStatTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return DragonStatData;
}

FItemData *UMyGameInstance::GetConsumeItemData(int code)
{
	auto ConsumeData = _ConsItemTable->FindRow<FItemData>(*FString::FromInt(code), TEXT(""));
	return ConsumeData;
}

FItemData *UMyGameInstance::GetEquipItemData(int code)
{
	auto EquipData = _EquipItemTable->FindRow<FItemData>(*FString::FromInt(code), TEXT(""));
	return EquipData;
}

TArray<FSellings *> UMyGameInstance::GetSellingData(int32 shop)
{
	TArray<FSellings *> sellingList;
	FSellings *sellingData = nullptr;

	for (int i = 0; i < SHOP_LIST_MAX; i++)
	{
		sellingData = _ShopLists[shop]->FindRow<FSellings>(*FString::FromInt(i), TEXT(""));
		sellingList.Add(sellingData);
	}

	return sellingList;
}

ABaseItem *UMyGameInstance::SellDataToItemData(FSellings *data)
{
	if (data->Type == ItemType::Equipment)
	{
		AEquipItem *equip = GetWorld()->SpawnActor<AEquipItem>(AEquipItem::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		equip->SetItemWithCode(data->Code);
		return Cast<ABaseItem>(equip);
	}
	else
	{
		ABaseItem *consume = GetWorld()->SpawnActor<ABaseItem>(ABaseItem::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		consume->SetItemWithCode(data->Code);
		return consume;
	}
}
