# YPK_RPG V2.0 </br>
- 유튜브링크 : https://youtu.be/NWj8hIFVd30</br>
- 패키징파일(Windows) : https://drive.google.com/drive/folders/1R1YOr0E5lGBl__Li2Lf_HMDNkwYBS-YR?usp=sharing</br>
- 패키징파일(Mac) : https://drive.google.com/drive/folders/18GrNxqSM3LWHmCPVZRnw6-RRE5BSR6jL</br>

## 📝 개요
본 프로젝트는 7주 동안 **TEAM_YP2K**에서 개발한 언리얼 엔진 기반으로 만든 다양한 스테이지와 다양한 몬스터를 사냥하며 성장하는 던전형 RPG게임입니다.🎮 
4인 팀으로 진행한 프로젝트이며, 깃허브를 활용하여 협업을 진행했습니다. 주요 클래스 및 구조를 C++ 코드 기반으로 설명합니다.

## 🔍 클래스 구조도
```
-MyGameInstance (게임 단계 및 데이터 관리)
-AActor
 ├── AMyEffectManager (이펙트 관리)
 ├── AMySoundManager (사운드 관리)
 ├── AMyUIManager (UI 관리)
 ├── AGameModeBase (게임 진행 관리)
 │   ├── AStartGameModeBase (시작 메뉴 게임 모드 클래스)
 │   ├── AMyGameModeBase (일반 게임 모드 클래스)
 │   │   ├── ANormalGameModeBase (사냥 스테이지 게임 모드)
 │   │   │   ├── AStage1NormalGameModeBase (스테이지1)
 │   │   │   ├── AStage2NormalGameModeBase (스테이지2)
 │   ├── ABossGameModeBase (보스 스테이지 게임 모드)
 │   │   │   ├── AStage1BossGameModeBase (스테이지1)
 │   │   │   ├── AStage2BossGameModeBase (스테이지2)
 │   ├── AHomeGameModeBase (마을 스테이지 게임 모드)
 ├── AMyCreature (ACharacter 상속)
 │   ├── AMyPlayer (플레이어)
 │   ├── AMyMonster (몬스터)
 │   │   ├── AMyNormalMonster (일반 몬스터)
 │   │   ├── AMyEpicMonster (에픽 몬스터)
 │   │   ├── AMyBossMonster (보스 몬스터)
 ├── AMyComponent (컴포넌트)
 │   ├── UStatComponent (스탯 관리)
 │   ├── UInventoryComponent (인벤토리 관리)
 │   ├── UShopComponent (상점 관리)
 ├── ABaseItem (아이템 베이스 클래스)
 │   ├── AEquipItem (장비 아이템 클래스)
 |   │   ├── Helmet (투구)
 |   │   ├── ShoulderArmor (어꺠)
 |   │   ├── UpperArmor (상의)
 |   │   ├── LowerArmor (하의)
 |   │   ├── Sword (무기)
 |   │   ├── Shield (방패)
 │   ├── AConsumeItem (소비 아이템 클래스)
 |   │   ├── Gold (돈)
 |   │   ├── Postion (포션)
 		.
		.
		.
		.
```

## 🔥 맡은 역할

### Player 및 Monster 구현
- **Skill,Stat UI 및 기능** 구현
- **장비 및 소비 Item** 구현
- **전투 시스템(가드,회피,몬스터처리시 경험치 및 아이템 획득)** 개발
- **체력 와 마나 및 경험치 UI** 
- **몬스터 AI(Behavior Tree) 구현** 전투 패턴 적용
- **AnimInstance 제작**
- 팀원이 제작한 UI와 연동확인 및 수정

### Stage 구현
- Stage이동을 위한 **Portal** 구현
- **Stage별 GameMode** 구현
- **GameInstance를 통한 데이터 관리**

### Boss Monster 구현
- **보스 등장 연출(Scene) 구현**
- **주변 사물과 상호작용을 이용한 기믹**
- **Behavior Tree 설계 및 AI 패턴 적용**</br>
<img width="600" alt="Image" src="https://github.com/user-attachments/assets/86d00f94-024d-475b-96bd-c79c1c9d002f" /> </br>

### Component 및 Manager 시스템 개발
- ** Sound 및 Effect 및 UI Manager로 관리**
```
// Map을 이용해 저장 및 관리,사용
void ASoundManager::PlaySound(FString name, FVector location)
{
	if (_soundEffectTable.Contains(name) == false)
		return;

	auto findSound = _soundEffectTable[name].FindByPredicate(
		[](ASoundEffect *soundEffect) -> bool
		{
			if (soundEffect->IsPlaying())
				return false;
			return true;
		});

	if (findSound)
		(*findSound)->Play(location);
}
```
- **Stat, Inventory를 Component로 설계하여 객체의 기능 모듈화**
- **Delegate**으로 이벤트 처리
```
//HP관련 이벤트 처리
void UStatComponent::SetHp(int32 hp)
{
	_curHp = hp;
	if (_curHp <= 0)
	{
		_deathDelegate.Broadcast();
		_deathDelegate.Clear();
		_curHp = 0;
	}
	if (_curHp > _maxHp)
	{
		_curHp = _maxHp;
	}

	float ratio = _curHp / (float)_maxHp;
	_PlHPDelegate.Broadcast(ratio);
}
// Delegate 바인딩
void AMyPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_KnightanimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (_KnightanimInstance->IsValidLowLevelFast())
	{
		_KnightanimInstance->OnMontageEnded.AddDynamic(this, &AMyPlayer::OnAttackEnded);
		_KnightanimInstance->_attackDelegate.AddUObject(this, &ACreature::AttackHit);
		_KnightanimInstance->_deathDelegate.AddUObject(this, &ACreature::Disable);
		_KnightanimInstance->_comboDelegate.AddUObject(this, &AMyPlayer::NextCombo);
	}
}

```
## ⚠️ 오류 상황과 해결 방안

###  GC오류  
🔍 **원인**</br>
> 잘못된 객체 참조및 알맞지 않은 UPROPERTY() 사용(맵 이동시 Item이 제대로 초기화 되지 않음)

✅ **해결 방법**  
> Crash Report 및 Log을 이용해 초기화 안된 객체 확인 후 Destroy()및 reset() 확인과 UPROPERTY() 확인 및 GC공부(refcount, mark and sweep)

------------------------------------------------------------------------------------------------------------------</br>

###  아이템과 인벤토리UI 연동 및 UI 오류
🔍 **원인**</br>
> 아이템과 인벤토리 컵포넌트와 UI담당 팀원과 충분한 소통을 하지 않아 오류 발생
> Texture과 Type을 서로 다르게 사용하고 있었음
> 서로 UI를 따로 따로 관리해 UI끼리 충돌 오류 

✅ **해결 방법**  
> 회의를 통해 문제 발견 및 해결 
> Item을 하드코딩해 구성하지않고 DataTable을 이용해 Code로 관리 및 사용
> UIManger을 통한 UI 정리
<img width="1420" alt="Image" src="https://github.com/user-attachments/assets/115ff265-d3b5-482d-95b0-10ae43a444c5" />

```
//해결 코드(item)
void ABaseItem::SetItemWithCode(int32 itemCode)
{
	auto gameinstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (gameinstance != nullptr)
	{
		FItemData *data = gameinstance->GetConsumeItemData(itemCode);
		if (data == nullptr || data->_Name == TEXT(""))
		{
			return;
		}

		ItemData = *data;
	}
}

//UIMnager
void AUIManager::OpenUI(UI_LIST ui)
{
	int32 UIindex = (int32)ui;

	if (UIindex > _uiList.Num())
		return;

	if (InventoryMutual(ui) || InterectMutual(ui))
		return;

	if (_isPauseWhenOpen[UIindex])
		pauseGame.Broadcast();

	if (ShouldCountUI(ui))
	{
		cnt++;
	}

	APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController && cnt > 0)
	{
		bool bIsCursorVisible = PlayerController->bShowMouseCursor;
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
	}
	_uiIsOpen[UIindex] = true;
}
```
------------------------------------------------------------------------------------------------------------------</br>

###  Map 이동시 기존 데이터 오류   
🔍 **원인**</br>
> OpenLevel함수로 Map이동시 기존데이터가 삭제됨

✅ **해결 방법**  
> GameInstance를 통해 이동전 데이터 Save 후 이동완료시 Load
```
//Save 
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

//Load
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
]
```

------------------------------------------------------------------------------------------------------------------</br>

###  몬스터가 스폰 될떄 마다 렉이 심하게 걸림
🔍 **원인**</br>
> 몬스터 스폰시 생성과 삭제를 매번 반복으로 인한 최적화 실패

✅ **해결 방법**  
> Object Pooling 사용 으로 메모리 최적화
```
// 몬스터 오브젝트풀링 (몬스터를 비활성 상태로 스폰해둠)
void ANormalGameModeBase::InitializeMonsterPool()
{
	if (!_monster) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int32 i = 0; i < 20; ++i)
	{
		ANormalMonster* Monster = GetWorld()->SpawnActor<ANormalMonster>(_monster, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (Monster)
		{
			Monster->SetActorHiddenInGame(true);
			Monster->SetActorEnableCollision(false);
			_monsterPool.Add(Monster);
		}
	}
}

// 몬스터 스폰시 아직 활성화 되지 않은 몬스터 활성화
for (int i = 0; i < size; ++i)
{
	ANormalMonster* AvailableMonster = nullptr;
	for (ANormalMonster* Monster : _monsterPool)
	{
		if (Monster->IsHidden())
		{
			AvailableMonster = Monster;
			break;
		}
	}
	if (!AvailableMonster) return;

	float SpawnRadius = 500.0f;

	FVector2D RandOffset = FMath::RandPointInCircle(SpawnRadius);
	FVector SpawnLocation = BaseLocation + FVector(RandOffset.X, RandOffset.Y, 0.0f);

	AvailableMonster->SetActorLocation(SpawnLocation);
	AvailableMonster->SetActorRotation(FRotator::ZeroRotator);
	AvailableMonster->SetActorHiddenInGame(false);
	AvailableMonster->SetActorEnableCollision(true);
}

```
------------------------------------------------------------------------------------------------------------------</br>

###  스킬이 이상한 곳에도 사용되는 현상 
🔍 **원인**</br>
> 마우스 포인터 위치의 값에 바로 스킬을 사용하기 때문에 벽면과 낭따러지에도 스킬이 사용됨

✅ **해결 방법**  
> ImpactNorma(법선벡터) 사용으로 일정 기울기에만 스킬이 사용되도록 수정
```
if (HitResult.bBlockingHit)
{
	if (HitResult.ImpactNormal.Z > 0.5f)
	{
		FVector NewLocation = HitResult.ImpactPoint;
		TargetSkillLocation = NewLocation;
		TargetSkillLocation.Z += 1.0f;

		SkillRotation = HitResult.ImpactNormal.Rotation();
		SpawnedDecalActor->SetActorLocation(TargetSkillLocation);
		SpawnedDecalActor->SetActorRotation(SkillRotation);
	}
}
```
------------------------------------------------------------------------------------------------------------------</br>

## 🚀 프로젝트를 통해 배운 점
1. **C++ 기반 객체 지향 설계** 🏗️
   - 상속 및 다형성을 활용하여 확장 가능한 게임 구조 설계
   - Unreal Engine의 Actor, Component 활용 경험

2. **팀 협업과 깃허브 활용** 🤝
   - 브랜치 전략을 활용한 효과적인 협업 (feature 브랜치 사용, Pull Request 리뷰)
   - 코드 리뷰를 통한 코드 품질 향상 및 유지보수성 증가

3. **게임 시스템 설계 및 구현** 🛠️
   - Object Pooling 기법을 활용한 최적화된 이펙트 및 사운드 관리
   - Component를 활용해 객체별로 독립적인 데이터 관리
   - AI 기반 파티 시스템과 몬스터 공격 및 보스 몬스터 특수 패턴 구현
   - UI기능 구현과 Delegate 활용
   - Unreal을 이용한 Anim제작
   - GameMode와 GameInstance를 이용해 게임 설계 및 데이터 관리


4. **게임 플레이 및 사용자 경험 향상** 🎨
   - 사운드와 이펙트를 결합하여 타격감 개선
   - 체력바 및 경험치 시스템을 적용하여 게임 몰입도 향상
