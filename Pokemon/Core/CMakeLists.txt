# Core/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)

# 收集 Core 文件夹下的源文件
file(GLOB CORE_SOURCES "*.h" "*.cpp")

# 生成静态库（供 Client 和 Server 链接）
add_library(CoreLib STATIC ${CORE_SOURCES})

# 链接 Common 模块（Core 依赖共用定义）和 Qt 核心模块
target_link_libraries(CoreLib PRIVATE CommonLib Qt6::Core)