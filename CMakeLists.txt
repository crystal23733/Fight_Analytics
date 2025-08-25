# CMake 최소 버전 지정 (3.16은 충분히 안정적인 버전)
cmake_minimum_required(VERSION 3.16)

# 프로젝트 이름과 버전 설정
project(FightAnalytics VERSION 1.0.0 LANGUAGES CXX)

# C++17 표준 사용 (std::optional, std::chrono 등을 위해)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 컴파일러별 최적화 옵션
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # 디버그 모드에서는 디버깅 정보 포함, 최적화 끔
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
    # 릴리즈 모드에서는 최적화 최대
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
endif()

# OpenCV 찾기 (필수 라이브러리)
find_package(OpenCV REQUIRED)
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV를 찾을 수 없습니다. 설치해주세요!")
endif()

# spdlog 찾기 (로깅용 - 선택사항)
find_package(spdlog QUIET)
if(spdlog_FOUND)
    message(STATUS "spdlog 발견됨 - 로깅 기능 활성화")
    add_definitions(-DUSE_SPDLOG)
else()
    message(STATUS "spdlog 없음 - 기본 cout 사용")
endif()

# 헤더 파일 경로 지정
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${OpenCV_INCLUDE_DIRS})

# 소스 파일들 자동으로 찾기
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.cc"
)

# 헤더 파일들 자동으로 찾기 (IDE에서 보기 좋게)
file(GLOB_RECURSE HEADERS 
    "include/*.h"
    "include/*.hpp"
)

# 실행 파일 생성
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# 라이브러리 링크
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

# spdlog가 있으면 링크
if(spdlog_FOUND)
    target_link_libraries(${PROJECT_NAME} spdlog::spdlog)
endif()

# 테스트 활성화
enable_testing()

# Catch2 찾기 (테스트용)
find_package(Catch2 QUIET)
if(Catch2_FOUND)
    message(STATUS "Catch2 발견됨 - 단위 테스트 활성화")
    
    # 테스트 소스 파일들
    file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
    
    if(TEST_SOURCES)
        # 테스트 실행 파일 생성 (main.cpp 제외)
        list(FILTER SOURCES EXCLUDE REGEX ".*main\\.cpp$")
        add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES} ${SOURCES})
        
        # 테스트용 라이브러리 링크
        target_link_libraries(${PROJECT_NAME}_tests 
            ${OpenCV_LIBS} 
            Catch2::Catch2WithMain
        )
        
        if(spdlog_FOUND)
            target_link_libraries(${PROJECT_NAME}_tests spdlog::spdlog)
        endif()
        
        # CTest에 등록
        add_test(NAME unit_tests COMMAND ${PROJECT_NAME}_tests)
    endif()
else()
    message(STATUS "Catch2 없음 - 테스트 비활성화")
endif()

# 설치 설정 (선택사항)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
