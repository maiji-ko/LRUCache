
#include <mutex>

template<typename Key, typename Value>
ThreadSafeLRUCache<Key, Value>::ThreadSafeLRUCache(size_t capacity)
    : m_capacity(capacity >= m_minCapacity && capacity < m_maxCapacity ? capacity : m_minCapacity) {}

// Get a value from thr cache (return shared_ptr to value if found)
template<typename Key, typename Value>
std::shared_ptr<Value> ThreadSafeLRUCache<Key, Value>::get(const Key& key)
{
    std::lock_guard<std::mutex> lock(m_lruCacheMutex);

    auto it = m_cache.find(key);
    if (it == m_cache.end()) {
        return nullptr;
    }

    // Check if weak_ptr is still valid
    auto sharedPtr = it->second.second.lock();
    if (!sharedPtr) {
        // Value has been expired, remove from cache
        m_lru.erase(it->second.first);
        m_cache.erase(it);
        return nullptr;
    }

    // Move to front of LRU list
    m_lru.splice(m_lru.begin(), m_lru, it->second.first);

    return sharedPtr;
}

// Put a value into the cache
template<typename Key, typename Value>
void ThreadSafeLRUCache<Key, Value>::put(const Key& key, std::shared_ptr<Value> value)
{
    if (!value) return;

    std::lock_guard<std::mutex> lock(m_lruCacheMutex);

    auto it = m_cache.find(key);
    if (it != m_cache.end()) {
        // Key exist, update value and move to front
        it->second.second = value;
        m_lru.splice(m_lru.begin(), m_lru, it->second.first);
        return;
    }

    // Check if we need to evict
    if (m_cache.size() >= m_capacity) {
        // evict the least recently used item
        auto last = m_lru.end();
        last--;
        m_cache.erase(*last);
        m_lru.pop_back();
    }

    // insert new item
    m_lru.push_front(key);
    m_cache[key] = {m_lru.begin(), value};
}

template<typename Key, typename Value>
void ThreadSafeLRUCache<Key, Value>::erase(const Key &key)
{
    std::lock_guard<std::mutex> lock(m_lruCacheMutex);

    auto it = m_cache.find(key);
    if (it != m_cache.end()) {
        m_lru.erase(it->second.first);
        m_cache.erase(it);
    }
}

template<typename Key, typename Value>
void ThreadSafeLRUCache<Key, Value>::clear()
{
    std::lock_guard<std::mutex> lock(m_lruCacheMutex);

    m_lru.clear();
    m_cache.clear();
}
template<typename Key, typename Value>
size_t ThreadSafeLRUCache<Key, Value>::size() const
{
    std::lock_guard<std::mutex> lock(m_lruCacheMutex);
    return m_cache.size();
}
