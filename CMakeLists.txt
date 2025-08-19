cmake_minimum_required(VERSION 3.10)
project(ctk-io-probe VERSION 1.0.0 LANGUAGES CXX)

# 打开 Qt 的 MOC / UIC / RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)

# 强制顺序：与 CONFIG += ordered 等价
# 注意：现代 CMake 推荐用 target_dependencies 而不是 ordered，
# 这里先按顺序 add_subdirectory 以保留原行为
add_subdirectory(application)
add_subdirectory(hierarch.da.datashow)
add_subdirectory(hierarch.da.recvctrl)
add_subdirectory(hierarch.da.sendctrl)
add_subdirectory(hierarch.da.com)
add_subdirectory(hierarch.da.mainwindow)

# 测试工程（可选）
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()