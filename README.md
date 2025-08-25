# 🥊 Fight Analytics - 격투기 영상 분석 프로그램

## 📖 프로젝트 개요
실시간 웹캠 또는 동영상 파일에서 격투기 동작을 분석하여 큰 움직임(타격)을 감지하고 "HIT!" 오버레이를 표시하는 C++ 프로그램입니다.

## 🎯 주요 기능
- **실시간 프레임 분석**: 웹캠 또는 동영상 파일 입력
- **움직임 감지**: 연속 프레임 차이를 통한 모션 디텍션
- **타격 판단**: 임계값 기반 HIT 이벤트 감지
- **시각적 피드백**: 실시간 "HIT!" 오버레이 표시
- **노이즈 필터링**: 가우시안 블러와 모폴로지를 통한 잡음 제거

## 🛠️ 기술 스택
- **언어**: C++17
- **라이브러리**: OpenCV 4.x
- **빌드 도구**: CMake
- **로깅**: spdlog
- **테스트**: Catch2

## 🏗️ 아키텍처

### 주요 클래스 구조
```
App (메인 애플리케이션)
├── Capture (영상 입력)
├── Preprocess (전처리)
├── MotionDetector (움직임 감지)
├── HitLogic (타격 판단)
├── OverlayRenderer (화면 표시)
└── Config (설정 관리)
```

### 데이터 흐름
1. **입력**: 웹캠/동영상에서 프레임 읽기
2. **전처리**: 그레이스케일 변환 + 가우시안 블러
3. **움직임 감지**: 프레임 차이 → 이진화 → 컨투어 추출
4. **타격 판단**: 움직임 에너지 계산 + 임계값 비교
5. **출력**: "HIT!" 오버레이 + 화면 표시

## ⚙️ 설정 파라미터
| 파라미터 | 기본값 | 설명 |
|---------|--------|------|
| blurKernel | 5 | 가우시안 블러 커널 크기 |
| thresholdVal | 25 | 프레임 차이 이진화 임계값 |
| minArea | 800 | 최소 움직임 영역 크기 |
| cooldownMs | 250 | HIT 이벤트 쿨다운 시간 |
| hitHoldMs | 150 | "HIT!" 표시 지속 시간 |

## 🚀 빌드 및 실행

### 사전 요구사항
```bash
# macOS (Homebrew)
brew install opencv cmake

# Ubuntu/Debian
sudo apt-get install libopencv-dev cmake

# Windows (vcpkg)
vcpkg install opencv4
```

### 빌드
```bash
mkdir build
cd build
cmake ..
make
```

### 실행
```bash
# 웹캠 사용
./fight_analytics

# 동영상 파일 사용
./fight_analytics video.mp4
```

## 🎮 사용법
- **ESC**: 프로그램 종료
- **스페이스바**: 스냅샷 저장
- **R**: 실시간 설정 리셋

## 🧪 테스트
```bash
cd build
ctest
```

## 📁 프로젝트 구조
```
Fight_Analytics/
├── src/                    # 소스 코드
│   ├── core/              # 핵심 클래스들
│   ├── utils/             # 유틸리티 함수들
│   └── main.cpp           # 메인 함수
├── include/               # 헤더 파일들
├── tests/                 # 단위 테스트
├── config/                # 설정 파일들
├── docs/                  # 문서
├── CMakeLists.txt         # CMake 설정
└── README.md
```

## 👥 개발 분담

### AI 담당 (복잡한 로직)
- MotionDetector 클래스 (프레임 차이 알고리즘)
- HitLogic 클래스 (타격 판단 로직)
- OverlayRenderer 클래스 (화면 렌더링)
- App 클래스 (메인 루프 및 조율)

### 사용자 담당 (기본 구조)
- Config 클래스 (설정 관리)
- Capture 클래스 (VideoCapture 래핑)
- Preprocess 클래스 (간단한 전처리)
- 단위 테스트 작성

## 🐛 알려진 이슈
- 조명 변화에 민감할 수 있음
- 빠른 움직임에서 모션 블러 발생 가능

## 🔮 향후 개선 사항
- 배경 차분법(MOG2) 도입
- Optical Flow 기반 속도 분석
- 포즈 추정을 통한 정확도 향상
- 얼굴/신체 부위별 가중치 적용

## 📄 라이선스
MIT License

## 📞 문의
프로젝트 관련 문의사항이나 버그 리포트는 Issues 탭을 이용해주세요.
