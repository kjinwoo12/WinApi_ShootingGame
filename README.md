# SPACE RAGE

Win32와 GDI+로 구현한 세로 스크롤 아케이드 슈팅입니다.
고등학교 시절 WinAPI 슈팅을 바탕으로, 기억을 더듬어 재구성한 리메이크입니다.

DirectX와 게임 엔진을 쓰지 않습니다. 창, 메시지 루프, 더블 버퍼, 스프라이트 그리기까지 Win32/GDI+로 직접 구성했습니다.
GDI+는 의도적 제약입니다. GPU API 대신 루프, 상태, 콘텐츠 확장의 책임 경계를 코드로 보이려고 골랐습니다.

## 프로젝트 목적

- 엔진 없이 게임 루프와 씬 상태의 소유권을 나눌 것
- 엔티티는 값 타입, 적 행동은 Strategy 테이블로 둘 것
- 적과 웨이브 추가는 작은 단위 변경으로 끝날 것

레이어: `App`, `Core`, `Gameplay`, `Render`.
적 확장: `IEnemyBehavior`와 `EnemyBehaviors` 등록 테이블. `Enemy` 상속 없음.

## 개요

좁은 히트박스, 그레이즈, 콤보, 레이지.
피격 시 화력 약화, 그레이즈로 게이지 회복.

| 항목 | 내용 |
|------|------|
| 장르 | 아케이드 슈팅 (세로 스크롤) |
| 해상도 | 700x800 고정 창 |
| 입력 | 키보드 |
| 씬 | Title, Playing, GameOver |
| 사운드 | 없음 (`winmm`는 타이머 정밀도만) |
| 테스트 / CI | 없음. 검증은 빌드와 플레이 루프 |

## 조작

| 키 | 동작 |
|----|------|
| WASD | 이동 |
| Space / Z | 발사 |
| Shift | 포커스 (저속, 히트박스 표시) |
| X / C | 폭탄 |
| Enter | 타이틀에서 시작 / 게임오버에서 타이틀 |
| Esc | 종료 |

## 빌드

요구: Windows, Visual Studio (C++ 데스크톱 개발 워크로드), Windows SDK.
프로젝트 도구 집합은 `v145`입니다.

1. `WinApiShooting.slnx`를 연다.
2. Debug x64 또는 Release x64.
3. 빌드 후 실행.

작업 디렉터리는 `WinApiShooting/` (vcxproj와 같음)을 권장합니다.
에셋은 실행 파일 기준으로 `Assets/SpaceRage`, `Assets/WenrexaUi` 후보 경로를 탐색합니다.

## 디렉터리

경로는 모두 `WinApiShooting/` 아래입니다.

```
App/        Win32 진입, GDI+ 수명, Game, 씬, HUD/타이틀/결과 오버레이
Core/       값 타입, World, SessionState, 입력, 충돌, Rgba8
Gameplay/   PlayingSession, Combat, 웨이브, IEnemyBehavior
Render/     Renderer, Assets(스프라이트 선택), WorldView, *Object::render, Sprite
Assets/     PNG (SpaceRage, WenrexaUi)
```

월드 표시: 엔티티 상태, `PlayerObject` 등 `*Object::render()`, `Assets` selector, `Sprite::draw`.
씬 UI는 `PlayingHudView`, `TitleOverlay`, `GameOverOverlay`가 소유합니다. Render는 프레임 버퍼와 스프라이트만 담당합니다.

### 적 추가

1. `EnemyKind` enum 끝에 추가
2. `XxxBehavior : IEnemyBehavior` (`configure` / `tick`)
3. `EnemyBehaviors.cpp` 테이블에 등록 (인덱스 = enum 순서)
4. 필요 시 `WaveDirector` / `WaveCatalog`에서 스폰

Behavior는 `EnemySystems`(탄과 이펙트)만 주입받습니다. 플레이어 무기, 폭탄 API에는 의존하지 않습니다.

## 구현 요약

- 업데이트와 렌더는 메인 스레드. 루프 중 디스크, 네트워크, `Sleep` 없음. 스프라이트 로드는 `Game::init`.
- `QueryPerformanceCounter` 기반 `DeltaTime`. 프레임 간격 상한 있음.
- 무기, 폭탄, 충돌, 탄은 역할별 클래스. Playing 오케스트레이션은 `PlayingSession::tick`.
- 중괄호 Allman. `auto` 미사용.
