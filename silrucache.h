#ifndef SILRUCACHE_H
#define SILRUCACHE_H

#include <vector>
#include <unordered_map>
#include <cstdint>
#include <algorithm>

template <typename Key, typename Value>
class SiLRUCache {
public:
    SiLRUCache(uint32_t cacheSize)
        : m_cacheSize(cacheSize), m_queue(0)
    {}

    /**
     * @brief Adds a new item into the cache.
     * 
     * @param key Cache Key
     * @param value Cache Value
     */
    void addItem(const Key& key, const Value& value) {
        checkQueueSize();
        m_cacheIndices.emplace({key, value});
        updateQueue(key);
    }

    /**
     * @brief Adds a new item into the cache.
     * 
     * @param key Cache Key
     * @param value Cache Value
     */
    void addItem(const Key& key, Value&& value) {
        checkQueueSize();
        m_cacheIndices.emplace(key, std::move(value));
        updateQueue(key);
    }

    /**
     * @brief Checks if the item is contained in the cache.
     * 
     * @param key Key of the cached item to look for.
     * @return true If the key is contained in the cache.
     * @return false If the key is not contained in the cache.
     */
    bool contains(const Key& key) {
        return m_cacheIndices.find(key) != m_cacheIndices.end();
    }

    /**
     * @brief Retrieve the item from the cache.
     * 
     * @param key Key of the cache item.
     * @return Value* Pointer to the value.
     */
    Value* getItem(const Key& key) {
        if (!contains(key)) return nullptr;
        updateQueue(key);
        return &m_cacheIndices.at(key);
    }

    /**
     * @brief Retrieve the item from the cache.
     * 
     * @param key Key of the cache item.
     * @return Value* Pointer to the value.
     */
    const Value* getItem(const Key& key) const {
        if (!contains(key)) return nullptr;
        updateQueue(key);
        return &m_cacheIndices.at(key);
    }

    /**
     * @brief Updates the least-recently-used tracker for that specific cache item.
     * 
     * @param key Key of the cache item.
     */
    void update(const Key& key) {
        updateQueue(key);
    }

    /**
     * @brief Reset the cache. Destroys all cache items.
     * 
     */
    void reset() {
        m_queue.clear();
        m_cacheIndices.clear();
    }

private:
    const uint32_t m_cacheSize;
    std::vector<Key> m_queue;
    std::unordered_map<Key, Value> m_cacheIndices;

    void updateQueue(const Key& key) {
        if (m_queue.size() > 0 && m_queue.back() == key) return;
        std::remove_if(m_queue.begin(), m_queue.end(), [&key](const auto& k) {
            return k == key;
        });
        m_queue.push_back(key);
    }

    void checkQueueSize() {
        if (m_queue.size() >= m_cacheSize) {
            m_cacheIndices.erase(m_queue.front());
            m_queue.erase(m_queue.begin(), m_queue.begin() + 1);
        }
    }
};

#endif
