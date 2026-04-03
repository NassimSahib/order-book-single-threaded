#pragma once 

#include <cstdint>

using OrderId = uint64_t;
using Price = uint64_t;
using Quantity = uint32_t;
using Timestamp = uint64_t;


enum class Side: uint8_t {
    Buy,
    Sell
};

struct Order {
    OrderId id;
    Timestamp timestamp;
    Price price;
    Quantity quantity;
    Side side;

};

static_assert(sizeof(Order) <= 32);