#include "thread_safe_lru_cache.h"
#include <iostream>
#include <string>

int main() {
    ThreadSafeLRUCache<int, std::string> cache(10);

    // 插入缓存项并保留 shared_ptr
    auto v1 = std::make_shared<std::string>("One");
    auto v2 = std::make_shared<std::string>("Two");

    cache.put(1, v1);
    cache.put(2, v2);

    std::cout << "Cache size: " << cache.size() << std::endl;

    // 访问 key = 1
    auto val = cache.get(1);
    if (val) {
        std::cout << "Retrieved value for key 1: " << *val << std::endl;
    }

    // 访问 key = 2
    val = cache.get(2);
    if (val) {
        std::cout << "Retrieved value for key 2: " << *val << std::endl;
    }

    // 插入缓存项并释放 shared_ptr
    {
        auto v3 = std::make_shared<std::string>("Three");
        cache.put(3, v3);
    }
    val = cache.get(3);
    if (!val) {
        std::cout << "Value for key 3 has been removed" << std::endl;
    }

    // 更新缓存项 2 的值为 Two_update
    auto updateV2 = std::make_shared<std::string>("Two_update");
    cache.put(2, updateV2);
    val = cache.get(2);
    if (val) {
        std::cout << "Updated value for key 2: " << *val << std::endl;
    }
    std::cout << "Cache size: " << cache.size() << std::endl;

    return 0;
}
