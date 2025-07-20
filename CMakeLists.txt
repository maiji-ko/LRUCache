# 设置最低版本要求
cmake_minimum_required(VERSION 3.30)
project(threadsafe_lru_cache VERSION 1.0.0 LANGUAGES CXX)

if (POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif ()

set(LRU_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(threadsafe_lru_cache INTERFACE)
target_include_directories(threadsafe_lru_cache
    INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${LRU_INCLUDE_DIR}>
)
target_compile_features(threadsafe_lru_cache INTERFACE cxx_std_20)

# 启用 demo 构建（可通过 -DBUILD_DEMO=OFF 关闭）
option(BUILD_DEMO "Build demo" ON)
if (BUILD_DEMO)
    add_subdirectory(demo)
endif ()
