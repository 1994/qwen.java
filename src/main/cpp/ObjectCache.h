//
// Created by r on 23-10-15.
//
#include "map"
#include <memory>
#include <mutex>
#include <utility>
#include "qwen.cpp/qwen.h"

#ifndef QWEN_JAVA_OBJECTCACHE_H
#define QWEN_JAVA_OBJECTCACHE_H


class ObjectCache {
public:
    ObjectCache(): nextKey(1){}

    long store(std::shared_ptr<qwen::Pipeline> obj) {
        std::lock_guard<std::mutex> lock(mutex);
        long key = nextKey++;
        cache[key] = std::move(obj);
        return key;
    }


    void remove(long key) {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = cache.find(key);
        if (it != cache.end()) {
            cache.erase(it);
        }
    }

    std::optional<std::shared_ptr<qwen::Pipeline>> get(long key) {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = cache.find(key);
        if (it != cache.end()) {
            return it->second;
        }
        return std::nullopt;
    }

private:
    std::map<long, std::shared_ptr<qwen::Pipeline>> cache;
    long nextKey;
    std::mutex mutex;
};


#endif //QWEN_JAVA_OBJECTCACHE_H
