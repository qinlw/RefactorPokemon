# Client/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)

# 收集 Client 文件夹下的源文件（包含客户端入口 main 函数等）
file(GLOB CLIENT_SOURCES "*.h" "*.cpp")

# 生成客户端可执行文件
add_executable(PokemonClient ${CLIENT_SOURCES})

# 链接 UI、Core、Common 模块及 Qt 网络/界面模块（客户端需要网络通信和界面）
target_link_libraries(PokemonClient PRIVATE UILib CoreLib CommonLib Qt6::Widgets Qt6::Network)