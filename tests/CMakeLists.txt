cmake_minimum_required(VERSION 3.10)

project(tst_allplugins VERSION 1.0.0 LANGUAGES CXX)

# Qt 自动化
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC OFF)   # 本测试工程没有 .qrc
set(CMAKE_CXX_STANDARD 11)

# 所需 Qt5 模块（含 testlib）
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Test)

# 公共头文件目录
# 公共头文件目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/core
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/pluginframework
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends
)

# 测试源文件
add_executable(tst_allplugins
    tst_allplugins.cpp
    # 头文件列出便于 IDE 浏览
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/IDACIFD.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/IDADataShowFactory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/IDAWidget.h
)

# 链接 Qt 库
target_link_libraries(tst_allplugins
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Test
	$<$<BOOL:${WIN32}>:${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/lib-windows-x64-msvc/CTKCore.lib>
    $<$<BOOL:${WIN32}>:${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/lib-windows-x64-msvc/CTKPluginFramework.lib>
)

# 等价于 CONFIG += testcase：让 CTest 识别
enable_testing()
add_test(NAME tst_allplugins COMMAND tst_allplugins)

# Windows 控制台（调试可见）
if(WIN32)
    set_target_properties(tst_allplugins PROPERTIES
        WIN32_EXECUTABLE FALSE   # 带控制台
    )
endif()

# macOS 不生成 .app
if(APPLE)
    set_target_properties(tst_allplugins PROPERTIES
        MACOSX_BUNDLE FALSE
    )
endif()