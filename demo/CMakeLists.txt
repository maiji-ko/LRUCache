add_executable(demo demo.cpp)
target_link_libraries(demo PRIVATE threadsafe_lru_cache)