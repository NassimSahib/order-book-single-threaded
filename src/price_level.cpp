#include "order.hpp"
#include "price_level.hpp"

void PriceLevel::AddOrder(const Order &order) {
    if (order.GetPrice() != price_) {
        throw std::logic_error("Price mismatch");
    }
    orders_.push_back(order);
}

Order& PriceLevel::Front() {
    return orders_.front();
}

const Order& PriceLevel::Front() const {
    return orders_.front();
}

void PriceLevel::PopFront() {
    orders_.pop_front();
}

Quantity PriceLevel::Match(Quantity quantity_to_match) {
    Quantity remaining = quantity_to_match;

    while (remaining > 0 && !orders_.empty()) {
        Order& front = Front();
        Quantity available = front.GetRemainingQuantity();

        if (available <= remaining) {
            front.ReduceQuantity(available);
            remaining -= available;
            PopFront();
        } else {
            front.ReduceQuantity(remaining);
            remaining = 0;
        }
    }

    return quantity_to_match - remaining;
}



