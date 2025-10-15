## 🚀 실행결과 — Lunar Lander

배경화면은 직접 제작했습니다.  
**규칙:** 위 화살표(↑)로 추력을 켜서 착륙지점(패드)에 **속도 15 이하**로 내려오면 **성공**,  
패드가 아닌 **바닥**에 닿거나, 패드에 내려와도 **속도 > 15**면 **실패**입니다.  
(↑ 키를 누르면 우주선 아래에 **불꽃(버스트)** 이 보입니다)

---

### 🎮 조작법
- **↑ (Up)**: 추력 On/Off  
- **← / →**: 좌우 이동  
- 좌측 상단에 `height / x / speed / fuel` 실시간 표시

---

### 🖼️ 스크린샷

1) **↑를 누르지 않았을 때** (자유낙하)
<img width="711" height="506" alt="image" src="https://github.com/user-attachments/assets/3e75d46c-8347-4a60-aea2-8dcae501776f" />

2) **↑를 눌렀을 때** (불꽃 표시, 연료 감소)
<img width="706" height="501" alt="image" src="https://github.com/user-attachments/assets/80e1b679-67f6-44b8-853e-fefa6273938d" />

3) **바닥에 착륙** → **실패** (패드가 아님)
<img width="705" height="508" alt="image" src="https://github.com/user-attachments/assets/67227afd-6f40-4689-99a1-f33a48e0f9fe" />

4) **패드에 속도 ≤ 15로 착륙** → **성공**
<img width="702" height="498" alt="image" src="https://github.com/user-attachments/assets/09c96df8-f1ed-439e-9a6b-72d88d0a6548" />


## 🧪 핵심 기술 요소 (Tech Highlights)
- **언어/패턴**: C++17, 클래스/캡슐화, `std::string`, 수학 연산, 조건·분기, 입력 이벤트 처리  
- **렌더링/UI**: **SFML Graphics**로 스프라이트(우주선/버스트), 텍스처 로딩, 텍스트 HUD(`height/x/speed/fuel`) 표시  
- **오디오**: **SFML Audio**로 부스터/이동/실패 사운드 재생(버퍼 로딩 → 사운드 트리거)  
- **게임 루프**: 고정 프레임(약 60 FPS) + 입력(↑/←/→) → **Update → Draw** 순서 확립  
- **물리 모델**: `velocity = velocity - thrust + gravity`, `position += velocity`  
- **판정 로직**: 착륙 패드 영역(x 범위) + **속도 임계값(≤ 15)** → `success` / 그 외 `failed`

## 🎯 프로젝트 의의 & 소감
- **학습 목표의 게임화**: 중력·추력·속도 제한 등 규칙을 직접 설계/구현하며 **수학적 모델(물리) → 코드**로 연결하는 경험을 얻음.  
- **실시간 시스템 감각**: 프레임 루프, 이벤트 처리, 상태 갱신/렌더링을 분리해 **게임 루프 아키텍처**를 체득.  
- **객체지향 설계 훈련**: 우주선 상태(연료/속도/텍스처/사운드)와 UI를 **클래스 기반으로 캡슐화**, 유지보수성과 확장성 강화.  
- **개인 소감**: *“이렇게 게임 형식으로 C++를 배우니까 재밌었음.”* 즉각적인 시각/청각 피드백 덕분에 개념이 빠르게 잡힘.





