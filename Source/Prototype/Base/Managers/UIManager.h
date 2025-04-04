// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UI/SkillWidget.h" 
#include "UIManager.generated.h"

UENUM()
enum class UI_LIST
{
	Inventory,
	Stat,
	Boss,
	Boss2,
	Shop,
	StartUI,
	Load,
	Options,
	Skill,
	PlayerBar,
	Login
};

DECLARE_MULTICAST_DELEGATE(PAUSE_GAME);
DECLARE_MULTICAST_DELEGATE(RESUM_GAME);

class UInventoryWidget;
class UStatWidget;
class UTexture2D;
class UBoss1Widget;
class UBoss2Widget;
class UShopWidget;
class UMainStartWidget;
class UPlayerBarWidget;
class ULoginWidget;


UCLASS()
class PROTOTYPE_API AUIManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OpenUI(UI_LIST ui);
	void CloseUI(UI_LIST ui);
	void CloseAll();
	void ToggleUI(UI_LIST ui);
	void SetPlayerUI(class UStatComponent* StatCom);

	UInventoryWidget *GetInventoryUI() { return _inventoryUI; }
	UStatWidget *GetStatUI() { return _statUI; }
	UBoss1Widget *GetBossUI() { return _bossUI; }
	UBoss2Widget *GetBoss2UI() { return _boss2UI; }
	UShopWidget *GetShopUI() { return _shopUI; }
	UMainStartWidget *GetStartUI() { return _startUI; }
	UUserWidget *GetOptionsUI() { return _options; }
	UTexture2D *GetDefaultTexture() { return _defaultTexture; }
	USkillWidget *GetSkillUI() {return _skillUI;}
	UPlayerBarWidget *GetPlayerBarUI() { return _playerBarUI; }
	ULoginWidget *GetLoginUI() { return _loginUI; }
	

	PAUSE_GAME pauseGame;
	RESUM_GAME resumGame;

private:
	bool InventoryMutual(UI_LIST invenUI);
	bool InterectMutual(UI_LIST interectUI);

	UPROPERTY()
	TArray<UUserWidget *> _uiList;

	UPROPERTY()
	TArray<bool> _uiIsOpen;

	UPROPERTY()
	TArray<bool> _isPauseWhenOpen;

	UPROPERTY()
	UInventoryWidget *_inventoryUI;

	UPROPERTY()
	UInventoryWidget *_statusUI;

	UPROPERTY()
	UStatWidget *_statUI;

	UPROPERTY()
	UTexture2D *_defaultTexture;

	UPROPERTY()
	UBoss1Widget *_bossUI;

	UPROPERTY()
	UBoss2Widget *_boss2UI;

	UPROPERTY()
	UShopWidget *_shopUI;

	UPROPERTY()
	UMainStartWidget *_startUI;

	UPROPERTY()
	UUserWidget *_loadUI;

	UPROPERTY()
	UUserWidget *_options;

	UPROPERTY()
	USkillWidget *_skillUI;

	UPROPERTY()
	UPlayerBarWidget *_playerBarUI;

	UPROPERTY()
	ULoginWidget *_loginUI;

	UPROPERTY()
	int32 cnt = 0;
};
