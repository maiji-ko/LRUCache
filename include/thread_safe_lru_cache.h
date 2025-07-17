//
// Created by PolarLightDance on 25-7-17.
//
#pragma once

#include <stdexcept>
#include <memory>

template<typename Key, typename Value>
class ThreadSafeLRUCache {
public:
    explicit ThreadSafeLRUCache(size_t capacity);
    ~ThreadSafeLRUCache() = default;

    // 禁止拷贝和赋值
    ThreadSafeLRUCache(const ThreadSafeLRUCache&) = delete;
    ThreadSafeLRUCache& operator=(const ThreadSafeLRUCache&) = delete;

private:
    // 缓存项大小
    size_t m_capacity;
};

#include "thread_safe_lru_cache.tpp"
