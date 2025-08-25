#include "core/config.h"
#include <sstream>

namespace FightAnalytics {

// ===== 생성자 구현 =====
Config::Config() {
    // 🎯 영상 처리 관련 기본값들 설정
    blurKernel_ = 5;
    thresholdVal_ = 25;     // 움직임 감지 민감도 (0-255)
    minArea_ = 800;         // 최소 움직임 크기 (픽셀)
    
    // 🎯 타격 판단 관련 기본값들 설정
    cooldownMs_ = 250;      // HIT 쿨다운 시간 (밀리초)
    hitHoldMs_ = 150;       // HIT 표시 지속 시간 (밀리초)
    
    // 🎯 화면 표시 관련 기본값들 설정
    hitTextScale_ = 2.0;    // 텍스트 크기 (2배 크기)
    hitTextThickness_ = 3;  // 텍스트 굵기 (굵게)
}

void Config::resetToDefaults() {
  blurKernel_ = 5;
  thresholdVal_ = 25;
  minArea_ = 800;
  cooldownMs_ = 250;
  hitHoldMs_ = 150;
  hitTextScale_ = 2.0;
  hitTextThickness_ = 3;
}

// ===== Setter 함수들 구현 =====

bool Config::setBlurKernel(int value) {
    // 🔍 유효성 검사: 홀수이고 3 이상이어야 함
    if (value < 3 || value % 2 == 0) {
        return false;  // 잘못된 값이면 거부
    }
    blurKernel_ = value;
    return true;  // 성공
}

bool Config::setThresholdVal(int value) {
    // 🔍 유효성 검사: 0~255 범위여야 함
    if (value < 0 || value > 255) {
        return false;
    }
    thresholdVal_ = value;
    return true;
}

bool Config::setMinArea(int value) {
    // 🔍 유효성 검사: 양수여야 함
    if (value <= 0) {
        return false;
    }
    minArea_ = value;
    return true;
}

bool Config::setCooldownMs(int value) {
    // 🔍 유효성 검사: 양수여야 함
    if (value <= 0) {
        return false;
    }
    cooldownMs_ = value;
    return true;
}

bool Config::setHitHoldMs(int value) {
    // 🔍 유효성 검사: 양수여야 함
    if (value <= 0) {
        return false;
    }
    hitHoldMs_ = value;
    return true;
}

bool Config::setHitTextScale(double value) {
    // 🔍 유효성 검사: 0.1 이상이어야 함
    if (value < 0.1) {
        return false;
    }
    hitTextScale_ = value;
    return true;
}

bool Config::setHitTextThickness(int value) {
    // 🔍 유효성 검사: 1 이상이어야 함
    if (value < 1) {
        return false;
    }
    hitTextThickness_ = value;
    return true;
}

// ===== 유틸리티 함수들 구현 =====

bool Config::isValid() const {
    // 🔍 모든 값이 유효한지 체크
    return (blurKernel_ >= 3 && blurKernel_ % 2 == 1) &&  // 홀수, 3 이상
           (thresholdVal_ >= 0 && thresholdVal_ <= 255) &&  // 0~255 범위
           (minArea_ > 0) &&                                // 양수
           (cooldownMs_ > 0) &&                             // 양수
           (hitHoldMs_ > 0) &&                              // 양수
           (hitTextScale_ >= 0.1) &&                       // 0.1 이상
           (hitTextThickness_ >= 1);                        // 1 이상
}

std::string Config::toString() const {
    // 🔍 설정 내용을 보기 좋게 문자열로 만들기
    std::stringstream ss;
    
    ss << "=== Fight Analytics Config ===\n";
    ss << "영상 처리:\n";
    ss << "  블러 커널: " << blurKernel_ << "\n";
    ss << "  임계값: " << thresholdVal_ << "\n";
    ss << "  최소 영역: " << minArea_ << " 픽셀\n";
    ss << "\n타격 판단:\n";
    ss << "  쿨다운: " << cooldownMs_ << " ms\n";
    ss << "  HIT 표시: " << hitHoldMs_ << " ms\n";
    ss << "\n화면 표시:\n";
    ss << "  텍스트 크기: " << hitTextScale_ << "\n";
    ss << "  텍스트 굵기: " << hitTextThickness_ << "\n";
    ss << "\n유효성: " << (isValid() ? "✅ 정상" : "❌ 오류") << "\n";
    
    return ss.str();
}

} // namespace FightAnalytics
