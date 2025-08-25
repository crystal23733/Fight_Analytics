#include "core/config.h"
#include <iostream>
#include <cassert>

using namespace FightAnalytics;

// 🎯 간단한 테스트 함수들
void test_constructor() {
    std::cout << "🧪 테스트 1: 생성자 기본값 확인..." << std::endl;
    
    Config config;
    
    // 기본값들이 올바르게 설정되었는지 확인
    assert(config.getBlurKernel() == 5);
    assert(config.getThresholdVal() == 25);
    assert(config.getMinArea() == 800);
    assert(config.getCooldownMs() == 250);
    assert(config.getHitHoldMs() == 150);
    assert(config.getHitTextScale() == 2.0);
    assert(config.getHitTextThickness() == 3);
    
    std::cout << "✅ 생성자 테스트 통과!" << std::endl;
}

void test_setters_valid() {
    std::cout << "\n🧪 테스트 2: 유효한 값 설정 확인..." << std::endl;
    
    Config config;
    
    // 유효한 값들 설정해보기
    assert(config.setBlurKernel(7) == true);      // 홀수 OK
    assert(config.setThresholdVal(50) == true);   // 0-255 범위 OK
    assert(config.setMinArea(1000) == true);      // 양수 OK
    assert(config.setCooldownMs(300) == true);    // 양수 OK
    assert(config.setHitHoldMs(200) == true);     // 양수 OK
    assert(config.setHitTextScale(1.5) == true);  // 0.1 이상 OK
    assert(config.setHitTextThickness(2) == true); // 1 이상 OK
    
    // 설정된 값들이 올바르게 저장되었는지 확인
    assert(config.getBlurKernel() == 7);
    assert(config.getThresholdVal() == 50);
    assert(config.getMinArea() == 1000);
    assert(config.getCooldownMs() == 300);
    assert(config.getHitHoldMs() == 200);
    assert(config.getHitTextScale() == 1.5);
    assert(config.getHitTextThickness() == 2);
    
    std::cout << "✅ 유효한 값 설정 테스트 통과!" << std::endl;
}

void test_setters_invalid() {
    std::cout << "\n🧪 테스트 3: 잘못된 값 거부 확인..." << std::endl;
    
    Config config;
    
    // 잘못된 값들이 거부되는지 확인
    assert(config.setBlurKernel(4) == false);      // 짝수 거부
    assert(config.setBlurKernel(2) == false);      // 3 미만 거부
    assert(config.setThresholdVal(-1) == false);   // 음수 거부
    assert(config.setThresholdVal(256) == false);  // 255 초과 거부
    assert(config.setMinArea(0) == false);         // 0 이하 거부
    assert(config.setMinArea(-10) == false);       // 음수 거부
    assert(config.setCooldownMs(0) == false);      // 0 이하 거부
    assert(config.setHitHoldMs(-5) == false);      // 음수 거부
    assert(config.setHitTextScale(0.05) == false); // 0.1 미만 거부
    assert(config.setHitTextThickness(0) == false); // 1 미만 거부
    
    // 잘못된 값을 시도했지만 기존 값은 그대로인지 확인
    assert(config.getBlurKernel() == 5);    // 기본값 유지
    assert(config.getThresholdVal() == 25); // 기본값 유지
    
    std::cout << "✅ 잘못된 값 거부 테스트 통과!" << std::endl;
}

void test_reset_to_defaults() {
    std::cout << "\n🧪 테스트 4: 기본값 리셋 확인..." << std::endl;
    
    Config config;
    
    // 값들을 변경
    config.setBlurKernel(9);
    config.setThresholdVal(100);
    config.setMinArea(1500);
    
    // 변경되었는지 확인
    assert(config.getBlurKernel() == 9);
    assert(config.getThresholdVal() == 100);
    assert(config.getMinArea() == 1500);
    
    // 리셋
    config.resetToDefaults();
    
    // 기본값으로 돌아왔는지 확인
    assert(config.getBlurKernel() == 5);
    assert(config.getThresholdVal() == 25);
    assert(config.getMinArea() == 800);
    assert(config.getCooldownMs() == 250);
    assert(config.getHitHoldMs() == 150);
    assert(config.getHitTextScale() == 2.0);
    assert(config.getHitTextThickness() == 3);
    
    std::cout << "✅ 기본값 리셋 테스트 통과!" << std::endl;
}

void test_is_valid() {
    std::cout << "\n🧪 테스트 5: 유효성 검사 확인..." << std::endl;
    
    Config config;
    
    // 기본 상태에서는 유효해야 함
    assert(config.isValid() == true);
    
    // 잘못된 값으로 변경 (private 멤버에 직접 접근할 수 없으므로
    // setter를 통해 유효한 값만 설정 가능)
    // 따라서 isValid()는 항상 true여야 함
    config.setBlurKernel(7);
    config.setThresholdVal(100);
    assert(config.isValid() == true);
    
    std::cout << "✅ 유효성 검사 테스트 통과!" << std::endl;
}

void test_to_string() {
    std::cout << "\n🧪 테스트 6: toString 함수 확인..." << std::endl;
    
    Config config;
    std::string result = config.toString();
    
    // 결과에 중요한 정보들이 포함되어 있는지 확인
    assert(result.find("Fight Analytics Config") != std::string::npos);
    assert(result.find("블러 커널") != std::string::npos);
    assert(result.find("5") != std::string::npos);  // 기본값 포함
    assert(result.find("✅ 정상") != std::string::npos);  // 유효성 표시
    
    std::cout << "✅ toString 테스트 통과!" << std::endl;
    
    std::cout << "\n📋 실제 toString 출력 결과:\n" << std::endl;
    std::cout << result << std::endl;
}

int main() {
    std::cout << "🚀 Config 클래스 테스트 시작!" << std::endl;
    std::cout << "================================" << std::endl;
    
    try {
        test_constructor();
        test_setters_valid();
        test_setters_invalid();
        test_reset_to_defaults();
        test_is_valid();
        test_to_string();
        
        std::cout << "\n🎉 모든 테스트 통과! Config 클래스가 완벽하게 작동합니다!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "❌ 테스트 실패: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
