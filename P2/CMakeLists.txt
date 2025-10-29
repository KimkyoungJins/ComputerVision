## 1. 최소 버전 지정
cmake_minimum_required(VERSION 3.10)

## 2. C++ 표준 설정 (가장 중요)
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## 3. 프로젝트 정의
project(MyProject)

## 4. 라이브러리 찾기
find_package(OpenCV REQUIRED)

## 5. 실행 파일 정의
add_executable(MyProject main.cpp)

## 6. 라이브러리 연결
target_link_libraries(MyProject ${OpenCV_LIBS})