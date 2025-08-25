#pragma once

#include <string>
#include <iostream>

/**
 * @file config.h
 * @brief 프로그램의 모든 설정값을 관리하는 클래스
 * 
 * 이 클래스는 마치 게임의 "설정" 메뉴와 같습니다.
 * 모든 중요한 숫자들(임계값, 크기 등)을 한 곳에 모아두어서
 * 나중에 쉽게 조정할 수 있게 만듭니다.
 */

namespace FightAnalytics {

/**
 * @class Config
 * @brief 격투기 분석 프로그램의 모든 설정값을 담는 클래스
 * 
 * 🎯 역할:
 * - 블러 강도, 임계값 등 모든 파라미터를 저장
 * - 기본값 제공
 * - 나중에 파일에서 읽거나 저장할 수 있는 구조
 */
class Config {
public:
    // ===== 생성자 =====
    /**
     * @brief 기본 생성자 - 모든 값을 권장 기본값으로 초기화
     */
    Config();

    // ===== Getter 함수들 (값 읽기) =====
    
    /** @brief 블러 커널 크기 가져오기 */
    int getBlurKernel() const { return blurKernel_; }
    
    /** @brief 임계값 가져오기 */
    int getThresholdVal() const { return thresholdVal_; }
    
    /** @brief 최소 영역 크기 가져오기 */
    int getMinArea() const { return minArea_; }
    
    /** @brief 쿨다운 시간 가져오기 */
    int getCooldownMs() const { return cooldownMs_; }
    
    /** @brief HIT 표시 시간 가져오기 */
    int getHitHoldMs() const { return hitHoldMs_; }
    
    /** @brief 텍스트 크기 가져오기 */
    double getHitTextScale() const { return hitTextScale_; }
    
    /** @brief 텍스트 두께 가져오기 */
    int getHitTextThickness() const { return hitTextThickness_; }

    // ===== Setter 함수들 (값 설정) =====
    
    /**
     * @brief 블러 커널 크기 설정 (홀수만 허용)
     * @param value 새로운 커널 크기 (3, 5, 7, 9 등)
     * @return 설정 성공 여부
     */
    bool setBlurKernel(int value);
    
    /**
     * @brief 임계값 설정 (0-255 범위)
     * @param value 새로운 임계값
     * @return 설정 성공 여부
     */
    bool setThresholdVal(int value);
    
    /**
     * @brief 최소 영역 크기 설정 (양수만 허용)
     * @param value 새로운 최소 영역 크기
     * @return 설정 성공 여부
     */
    bool setMinArea(int value);
    
    /**
     * @brief 쿨다운 시간 설정 (양수만 허용)
     * @param value 새로운 쿨다운 시간 (밀리초)
     * @return 설정 성공 여부
     */
    bool setCooldownMs(int value);
    
    /**
     * @brief HIT 표시 시간 설정 (양수만 허용)
     * @param value 새로운 표시 시간 (밀리초)
     * @return 설정 성공 여부
     */
    bool setHitHoldMs(int value);
    
    /**
     * @brief 텍스트 크기 설정 (양수만 허용)
     * @param value 새로운 텍스트 크기
     * @return 설정 성공 여부
     */
    bool setHitTextScale(double value);
    
    /**
     * @brief 텍스트 두께 설정 (양수만 허용)
     * @param value 새로운 텍스트 두께
     * @return 설정 성공 여부
     */
    bool setHitTextThickness(int value);

    // ===== 유틸리티 함수들 =====
    
    /**
     * @brief 설정값들이 유효한지 검사
     * @return true = 모든 설정이 올바름, false = 문제 있음
     * 
     * 🔍 예시: blurKernel이 홀수인지, thresholdVal이 0-255 범위인지 확인
     */
    bool isValid() const;
    
    /**
     * @brief 모든 설정을 기본값으로 리셋
     */
    void resetToDefaults();
    
    /**
     * @brief 설정 내용을 문자열로 출력 (디버깅용)
     * @return 설정값들을 보기 좋게 정리한 문자열
     */
    std::string toString() const;

private:
    // ===== 영상 처리 관련 설정 =====
    
    /**
     * @brief 가우시안 블러 커널 크기 (홀수여야 함)
     * 
     * 🔍 설명: 노이즈를 줄이기 위한 블러의 강도
     * - 작을수록: 선명하지만 노이즈 많음
     * - 클수록: 부드럽지만 디테일 손실
     */
         int blurKernel_;
     
     /**
      * @brief 프레임 차이 이진화 임계값 (0-255)
      * 
      * 🔍 설명: "얼마나 큰 변화를 움직임으로 볼 것인가?"
      * - 낮을수록: 작은 움직임도 감지 (민감함)
      * - 높을수록: 큰 움직임만 감지 (둔감함)
      */
     int thresholdVal_;
     
     /**
      * @brief 최소 움직임 영역 크기 (픽셀 단위)
      * 
      * 🔍 설명: 이것보다 작은 움직임은 무시
      * - 카메라 떨림이나 작은 노이즈 제거용
      * - 너무 크면 실제 타격도 놓칠 수 있음
      */
     int minArea_;

     // ===== 타격 판단 관련 설정 =====
     
     /**
      * @brief HIT 이벤트 쿨다운 시간 (밀리초)
      * 
      * 🔍 설명: HIT 한 번 뜨고 나서 다음 HIT까지 기다리는 시간
      * - 너무 짧으면: "HIT! HIT! HIT!" 연속으로 뜸
      * - 너무 길면: 연속 공격을 놓칠 수 있음
      */
     int cooldownMs_;
     
     /**
      * @brief "HIT!" 텍스트 표시 지속 시간 (밀리초)
      * 
      * 🔍 설명: 화면에 "HIT!" 글자가 얼마나 오래 보일지
      * - 너무 짧으면: 금방 사라져서 못 봄
      * - 너무 길면: 화면이 지저분해짐
      */
     int hitHoldMs_;

     // ===== 화면 표시 관련 설정 =====
     
     /**
      * @brief HIT 텍스트 크기 (OpenCV putText의 fontScale)
      * 
      * 🔍 설명: "HIT!" 글자의 크기
      * - 1.0 = 보통 크기
      * - 2.0 = 두 배 크기
      */
     double hitTextScale_;
     
     /**
      * @brief HIT 텍스트 두께 (OpenCV putText의 thickness)
      * 
      * 🔍 설명: "HIT!" 글자의 굵기
      * - 1 = 얇음
      * - 3 = 굵음
      */
     int hitTextThickness_;

    // ===== 유틸리티 함수들 =====
    
    /**
     * @brief 설정값들이 유효한지 검사
     * @return true = 모든 설정이 올바름, false = 문제 있음
     * 
     * 🔍 예시: blurKernel이 홀수인지, thresholdVal이 0-255 범위인지 확인
     */
    bool isValid() const;
    
    /**
     * @brief 모든 설정을 기본값으로 리셋
     */
    void resetToDefaults();
    
    /**
     * @brief 설정 내용을 문자열로 출력 (디버깅용)
     * @return 설정값들을 보기 좋게 정리한 문자열
     */
    std::string toString() const;
};

} // namespace FightAnalytics
