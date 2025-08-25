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

} // namespace FightAnalytics
