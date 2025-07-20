//
// Created by PolarLightDance on 25-7-17.
//
#pragma once

#include <list>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <iostream>

template<typename Key, typename Value>
class ThreadSafeLRUCache {
public:
    explicit ThreadSafeLRUCache(size_t capacity);
    ~ThreadSafeLRUCache() = default;

    ThreadSafeLRUCache(const ThreadSafeLRUCache&) = delete;
    ThreadSafeLRUCache& operator=(const ThreadSafeLRUCache&) = delete;

    // Get cahe item
    std::shared_ptr<Value> get(const Key& key);

    // Put cache item
    void put(const Key& key, std::shared_ptr<Value> value);

    // Delete cache item
    void erase(const Key& key);

    // Clear all cache items
    void clear();

    // Get current cache size
    size_t size() const;

private:
    // Cache capacity
    static constexpr size_t m_minCapacity = 10;
    static constexpr size_t m_maxCapacity = 1000;
    size_t m_capacity;

    // LRU list(most recent used item at front)
    std::list<Key> m_lru;

    // Cache item key -> {iterator in LRU list, weak_ptr<Value>}
    std::unordered_map<Key,
        std::pair<typename std::list<Key>::iterator, std::weak_ptr<Value>>> m_cache;

    mutable std::mutex m_lruCacheMutex;
};

#include "thread_safe_lru_cache.tpp"
