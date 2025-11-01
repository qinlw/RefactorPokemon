# Server/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)

# 收集 Server 文件夹下的源文件（包含服务器入口 main 函数等）
file(GLOB SERVER_SOURCES "*.h" "*.cpp")

# 生成服务器端可执行文件
add_executable(PokemonServer ${SERVER_SOURCES})

# 链接 Core 和 Common 模块（服务器需要核心逻辑和共用协议）及 Qt 网络模块（服务器需要网络通信）
target_link_libraries(PokemonServer PRIVATE CoreLib CommonLib Qt6::Network)