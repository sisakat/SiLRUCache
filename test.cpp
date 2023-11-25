#include <catch2/catch_amalgamated.hpp>
#include "silrucache.h"

#include <memory>
#include <string>

TEST_CASE("Insert and get item with primitive type") {
    SiLRUCache<int, int> cache(10);
    cache.addItem(1, 10);
    cache.addItem(2, 20);
    REQUIRE(cache.getItem(1).value() == 10);
    REQUIRE(cache.getItem(2).value() == 20);
}

TEST_CASE("Insert three items with cache size of 2") {
    SiLRUCache<int, int> cache(2);
    cache.addItem(1, 10);
    cache.addItem(2, 20);
    cache.addItem(3, 30);
    REQUIRE(cache.getItem(2).value() == 20);
    REQUIRE(cache.getItem(3).value() == 30);
    REQUIRE_FALSE(cache.contains(1));
}

TEST_CASE("Insert non-moveable cache items") {
    SiLRUCache<int, std::unique_ptr<int>> cache(1);
    cache.addItem(1, std::make_unique<int>(10));
    cache.addItem(2, std::make_unique<int>(20));
    REQUIRE(*(cache.getItem(2).value()) == 20);
    REQUIRE_FALSE(cache.contains(1));
}

TEST_CASE("Check if least recently used are removed") {
    SiLRUCache<int, int> cache(5);
    cache.addItem(1, 10);
    cache.addItem(2, 20);
    cache.addItem(3, 30);
    cache.addItem(4, 40);
    cache.addItem(5, 50);

    cache.getItem(1);
    cache.getItem(2);
    cache.getItem(3);
    cache.getItem(5);
    cache.getItem(2);
    cache.addItem(6, 60);

    REQUIRE(cache.getItem(1).value() == 10);
    REQUIRE(cache.getItem(6).value() == 60);
    REQUIRE_FALSE(cache.contains(4));
}

TEST_CASE("Cache item with custom size") {
    SiLRUCache<int, int, int, 2> cache(4); // can hold 2 items
    cache.addItem(1, 10);
    cache.addItem(2, SiLRUCacheItem<int, int, 2>(20));
    SiLRUCacheItem<int, int, 2> item3;
    item3.value() = 30;
    cache.addItem(3, item3);
    REQUIRE(cache.size() == 4);
}

TEST_CASE("Insert cache item which is to big for cache") {
    SiLRUCache<int, std::string> cache(10);
    SiLRUCacheItem<std::string> item("test", 100);
    REQUIRE_THROWS_AS(cache.addItem(1, item), std::runtime_error);
}
