
template<typename Key, typename Value>
ThreadSafeLRUCache<Key, Value>::ThreadSafeLRUCache(size_t capacity) : m_capacity(capacity) {
    if (capacity == 0) {
        throw std::invalid_argument("Cache capacity must be positive.");
    }
}
