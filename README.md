# YPK_MainProject(Temp)</br>
- 유튜브링크 : https://youtu.be/NWj8hIFVd30</br>
- 패키징파일 : https://drive.google.com/drive/folders/1R1YOr0E5lGBl__Li2Lf_HMDNkwYBS-YR?usp=sharing</br>

## 📝 개요
본 프로젝트는 2달 동안 **TEAM_YP2K**에서 개발한 언리얼 엔진 기반 3D 액션 게임입니다. 🎮  
4인 팀으로 진행한 프로젝트이며, 깃허브를 활용하여 협업을 진행했습니다. 주요 클래스 및 구조를 C++ 코드 기반으로 설명합니다.

## 🔥 맡은 역할
### Player 및 Monster 구현
- **기사(Knight) / 궁수(Archer) 캐릭터 구현** (근거리/원거리 전투)
- **전투 시스템** 개발
- **체력 및 경험치 UI** 연동
- **몬스터 AI 구현** 및 **AI을 활용한 파티 시스템 구현** 전투 패턴 적용
- **AnimInstance 제작** 및 캐릭터 애니메이션 연동
- 팀원이 제작한 코드와 연동확인 및 수정

### Boss Monster 구현
- **보스 등장 연출(Scene) 구현**
- **Behavior Tree 설계 및 AI 패턴 적용**
- **AggroComponent를 이용한 공격 대상 결정 로직 개발**

### Component 및 Manager 시스템 개발
- **사운드 및 이펙트 관리** (Object Pooling 기법 활용)
- **Stat, Aggro를 Component로 설계하여 객체의 기능 모듈화**

## 🎯 프로젝트 기획
- 🏰 **기사(Knight)**와 🏹 **궁수(Archer)**를 선택하여 플레이하는 3D 액션 RPG
- 👾 다양한 **몬스터 및 보스 몬스터**와의 전투 구현
- 🛒 **NPC와 상호작용을 통한 상점 시스템** 구현
- ✨ **스킬 이펙트 및 사운드를 활용한 타격감 있는 전투 시스템**
- 🎭 **게임 진행 및 스테이지 관리 기능** 구현
- 🔗 **GitHub를 이용한 협업 및 코드 리뷰 체계 구축**
- 💡 **C++의 객체 지향적 특징 활용**
- ⚙️ **컴포넌트 및 싱글톤 패턴을 활용한 매니저 시스템 구현**
- 🧠 **Unreal Engine의 AI, UI, Animation 기능 활용 및 응용**

## 🔍 클래스 구조도
```
AActor
 ├── AMyEffectManager (이펙트 관리)
 ├── AMySoundManager (사운드 관리)
 ├── AMyCreature (ACharacter 상속)
 │   ├── AMyPlayer (플레이어)
 │   │   ├── AMyKnight (기사, 근접 공격)
 │   │   ├── AMyArcher (궁수, 원거리 공격)
 │   ├── AMyMonster (몬스터)
 │   │   ├── AMyBaseMonster (일반 몬스터)
 │   │   ├── AMyBossMonster (보스 몬스터)
 ├── AGameModeBase (게임 진행 관리)
     ├── AMyGameModeBase (일반 게임 모드 클래스)
     ├── AMyBossGameModeBase (보스 게임 모드 클래스)

```
## ⚠️ 오류 상황과 해결 방안

### 1️⃣ GitHub 충돌 및 컴파일 에러 ❌  
🔍 **원인**</br>
>소통 부족으로 인한 브랜치 충돌 또는 잘못된 병합으로 인한 컴파일 오류 발생  

✅ **해결 방법**  
>주기적인 회의를 통해 진행 상황을 공유하고 GitHub 활용 방식 조율  
>`Develop` 브랜치에서 병합 및 버그 테스트 후 `Main` 브랜치로 반영  

### 2️⃣ 사운드 및 이펙트 미재생 🔊🚫  
🔍 **원인**  
>사운드/이펙트의 경로 설정 오류 또는 정리되지 않은 데이터  

✅ **해결 방법**  
>`AMyEffectManager` 및 `AMySoundManager`를 통해 중앙 관리  
>경로 설정 및 리소스 파일 유효성 점검  

### 3️⃣ 몬스터 AI 오작동 👾⚠️  
🔍 **원인**  
>`BTTask` 및 `Behavior Tree` 연결 오류  

✅ **해결 방법**  
>`BTTask` 및 `AIController` 관련 코드 수정  
>`BehaviorTree` 및 `Blackboard` 설정 확인  

### 4️⃣ 플레이어 애니메이션 적용 오류 🎭🚫  
🔍 **원인**  
>`AnimInstance` 및 `Notify` 설정 오류  

✅ **해결 방법**  
>`AnimInstance`의 `Notify` 및 `Delegate` 바인드 설정 확인 및 수정  

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
   - UI기능 구현과 Deligate 활용
   - Unreal을 이용한 Anim제작

4. **게임 플레이 및 사용자 경험 향상** 🎨
   - 사운드와 이펙트를 결합하여 타격감 개선
   - 체력바 및 경험치 시스템을 적용하여 게임 몰입도 향상
