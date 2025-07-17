# 设置最低版本要求
cmake_minimum_required(VERSION 3.30)

# 项目名称和版本（可选）
project(threadsafe_lru_cache VERSION 1.0.0 LANGUAGES CXX)

# 设置编译器策略，确保 C++ 标准正确应用
if (POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif ()

# 定义项目头文件目录路径
set(LRU_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# 创建接口库
add_library(threadsafe_lru_cache INTERFACE)

# 设置接口库的包含目录
target_include_directories(threadsafe_lru_cache
    INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${LRU_INCLUDE_DIR}>
)

# 可选：声明编译特性
target_compile_features(threadsafe_lru_cache INTERFACE cxx_std_20)

# 可选：启用测试构建（可通过 -DBUILD_TESTS=OFF 关闭）
option(BUILD_TESTS "Build tests" ON)
if (BUILD_TESTS)
    add_subdirectory(test)
endif ()
