#include "order.hpp"
#include "price_level.hpp"
#include "order_book.hpp"

#include <iostream>

bool OrderBook::CanMatch(const Order &incoming) const {
    if (incoming.GetSide() == Side::Buy) {
        if (asks_.empty()) 
            return false;
        auto best_ask = asks_.begin();
        if (incoming.GetPrice() >= best_ask->first)
            return true;
        return false;
    }
    else {
        if (bids_.empty())
            return false;
        auto best_bid = bids_.begin();
        if (incoming.GetPrice() <= best_bid->first) 
            return true;

        return false;
    } 
}

void OrderBook::Match(Order &incoming) {
    while (incoming.GetRemainingQuantity() && CanMatch(incoming)) {
        
        auto& book = (incoming.GetSide() == Side::Buy) ? asks_ : bids_;


    }
}