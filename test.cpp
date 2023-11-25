#include <catch2/catch_amalgamated.hpp>
#include "silrucache.h"

#include <memory>

TEST_CASE("Insert and get item with primitive type") {
    SiLRUCache<int, int> cache(10);
    cache.addItem(1, 10);
    cache.addItem(2, 20);
    REQUIRE(*cache.getItem(1) == 10);
    REQUIRE(*cache.getItem(2) == 20);
}

TEST_CASE("Insert three items with cache size of 2") {
    SiLRUCache<int, int> cache(2);
    cache.addItem(1, 10);
    cache.addItem(2, 20);
    cache.addItem(3, 30);
    REQUIRE(*cache.getItem(2) == 20);
    REQUIRE(*cache.getItem(3) == 30);
    REQUIRE(cache.getItem(1) == nullptr);
}

TEST_CASE("Insert non-moveable cache items") {
    SiLRUCache<int, std::unique_ptr<int>> cache(1);
    cache.addItem(1, std::make_unique<int>(10));
    cache.addItem(2, std::make_unique<int>(20));
    REQUIRE(*(*cache.getItem(2)) == 20);
    REQUIRE(cache.getItem(1) == nullptr);
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

    REQUIRE(*cache.getItem(1) == 10);
    REQUIRE(*cache.getItem(6) == 60);
    REQUIRE(cache.getItem(4) == nullptr);
}
