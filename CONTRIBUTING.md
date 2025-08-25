# 🤝 기여 가이드라인

Fight Analytics 프로젝트에 기여해주셔서 감사합니다!

## 📋 커밋 컨벤션

### 커밋 메시지 형식
```
<타입>(<범위>): <제목>

<본문 (선택사항)>

<푸터 (선택사항)>
```

### 커밋 타입
- **feat**: 새로운 기능 추가
- **fix**: 버그 수정
- **docs**: 문서 변경
- **style**: 코드 포맷팅, 세미콜론 누락 등 (기능 변경 없음)
- **refactor**: 코드 리팩토링
- **test**: 테스트 코드 추가/수정
- **chore**: 빌드 과정이나 보조 도구 변경

### 범위 (선택사항)
- **core**: 핵심 클래스들 (Capture, MotionDetector 등)
- **ui**: 사용자 인터페이스
- **config**: 설정 관련
- **test**: 테스트 관련
- **build**: 빌드 시스템

### 예시
```bash
feat(core): MotionDetector에 배경 차분법 추가

MOG2 알고리즘을 사용하여 배경 차분법을 구현했습니다.
이를 통해 조명 변화에 더 강건한 움직임 감지가 가능합니다.

Closes #15
```

## 🌿 브랜치 전략

### 브랜치 명명 규칙
- **feature/**: 새로운 기능 개발
  - 예: `feature/motion-detection`
- **fix/**: 버그 수정
  - 예: `fix/camera-initialization`
- **docs/**: 문서 작업
  - 예: `docs/api-documentation`
- **refactor/**: 코드 리팩토링
  - 예: `refactor/hit-logic-optimization`

### 워크플로우
1. **main** 브랜치에서 새 브랜치 생성
2. 기능 개발/버그 수정
3. 커밋 & 푸시
4. Pull Request 생성
5. 코드 리뷰 및 머지

## 🔍 코드 스타일

### C++ 스타일 가이드
- **클래스명**: PascalCase (예: `MotionDetector`)
- **함수명**: camelCase (예: `computeMask`)
- **변수명**: camelCase (예: `motionArea`)
- **상수명**: UPPER_SNAKE_CASE (예: `MAX_CONTOURS`)
- **파일명**: snake_case (예: `motion_detector.cpp`)

### 헤더 가드
```cpp
#pragma once
```

### 포함 순서
1. 해당 cpp의 헤더파일
2. C++ 표준 라이브러리
3. 외부 라이브러리 (OpenCV 등)
4. 프로젝트 내 헤더파일

```cpp
#include "motion_detector.h"

#include <vector>
#include <chrono>

#include <opencv2/opencv.hpp>

#include "config.h"
```

## 🧪 테스트 가이드라인

### 테스트 작성 규칙
- 모든 새로운 기능에 대해 단위 테스트 작성
- 테스트 함수명: `TEST_CASE("클래스명 - 테스트내용")`
- Given-When-Then 패턴 사용

### 예시
```cpp
TEST_CASE("MotionDetector - 움직임이 없을 때 빈 영역 반환") {
    // Given
    MotionDetector detector;
    cv::Mat staticFrame = cv::Mat::zeros(480, 640, CV_8UC1);
    
    // When
    cv::Mat mask;
    detector.computeMask(staticFrame, mask);
    auto stats = detector.extractStats(mask);
    
    // Then
    REQUIRE(stats.totalArea == 0);
}
```

## 📝 문서화

### 주석 작성
- 복잡한 알고리즘은 단계별로 주석 추가
- 클래스와 공개 함수에는 Doxygen 스타일 주석

```cpp
/**
 * @brief 연속 프레임 간의 차이를 계산하여 움직임을 감지합니다.
 * @param gray 현재 프레임 (그레이스케일)
 * @param mask 출력 마스크 (이진 이미지)
 */
void computeMask(const cv::Mat& gray, cv::Mat& mask);
```

## 🚀 Pull Request 가이드라인

### PR 생성 전 체크리스트
- [ ] 코드가 빌드되고 테스트가 통과하는지 확인
- [ ] 관련 문서가 업데이트되었는지 확인
- [ ] 커밋 메시지가 컨벤션을 따르는지 확인
- [ ] 코드 스타일 가이드를 준수하는지 확인

### PR 설명 작성
- 변경 사항에 대한 명확한 설명
- 관련 이슈 번호 포함
- 테스트 결과 포함
- 스크린샷 (UI 변경 시)

## 🐛 이슈 리포팅

### 버그 리포트 시 포함 정보
- 운영체제 및 버전
- OpenCV 버전
- 컴파일러 정보
- 재현 단계
- 예상 결과 vs 실제 결과
- 로그나 에러 메시지

### 기능 요청 시 포함 정보
- 사용 사례 설명
- 제안하는 해결책
- 우선순위 (높음/보통/낮음)
- 참고 자료나 예시

## ❓ 질문하기

프로젝트 관련 질문이 있으시면:
1. 먼저 README와 문서를 확인해주세요
2. 기존 이슈를 검색해주세요
3. 해결되지 않으면 새 이슈를 생성해주세요

감사합니다! 🙏
