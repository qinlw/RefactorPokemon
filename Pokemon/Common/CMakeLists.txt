# Common/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)

# 收集 Common 文件夹下的所有源文件（后续添加的 .h/.cpp 会自动包含）
file(GLOB COMMON_SOURCES "*.h" "*.cpp")

# 生成静态库（供 Client 和 Server 链接）
add_library(CommonLib STATIC ${COMMON_SOURCES})

# 链接 Qt 核心模块（共用代码可能用到的基础功能）
target_link_libraries(CommonLib PRIVATE Qt6::Core)