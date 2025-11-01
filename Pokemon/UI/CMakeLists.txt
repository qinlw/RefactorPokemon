# UI/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)

# 收集 UI 文件夹下的源文件
file(GLOB UI_SOURCES "*.h" "*.cpp")

# 生成静态库（供 Client 链接，Server 可能不需要 UI）
add_library(UILib STATIC ${UI_SOURCES})

# 链接 Core 模块（UI 需要显示核心逻辑数据）、Common 模块（共用定义）和 Qt 界面模块
target_link_libraries(UILib PRIVATE CoreLib CommonLib Qt6::Widgets)