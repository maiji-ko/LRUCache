#include "thread_safe_lru_cache.h"
#include <iostream>
#include <string>

int main()
{
    try {
        // 创建一个容量为3的缓存
        ThreadSafeLRUCache<int, std::string> cache(0);
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}
