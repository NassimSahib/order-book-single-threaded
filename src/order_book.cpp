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
        if (incoming.GetSide() == Side::Buy) {
            if (asks_.empty()) break;

            auto best_level = asks_.begin();

            Quantity matched = best_level->second.Match(incoming.GetRemainingQuantity());
                incoming.ReduceQuantity(matched);

                if (best_level->second.Empty()) {
                    asks_.erase(best_level);
                }
            } else {
                if (bids_.empty()) break;

                auto best_level = bids_.begin();

                Quantity matched = best_level->second.Match(incoming.GetRemainingQuantity());
                incoming.ReduceQuantity(matched);

                if (best_level->second.Empty()) {
                    bids_.erase(best_level);
                }
                
            }
        }
    }

    void OrderBook::AddOrder(Order order) {
        Match(order);
        if (order.GetRemainingQuantity() > 0) 
            AddToBook(order);
    }