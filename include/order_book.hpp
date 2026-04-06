#pragma once

#include <map>
#include "price_level.hpp"

class OrderBook
{
private:
    // Buyside (highest price first)
    std::map<Price, PriceLevel, std::greater<>> bids_;

    // Sell side (lowest price first)
    std::map<Price, PriceLevel, std::less<>> asks_;

public:
    OrderBook() = default;

    // Core API
    void AddOrder(Order order);

private:
    // Matching logic
    void Match(Order &incoming);

    // Helpers
    void AddToBook(const Order &order);

    bool CanMatch(const Order &incoming) const;
}