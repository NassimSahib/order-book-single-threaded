#include "order.hpp"
#include "price_level.hpp"

void PriceLevel::AddOrder(const Order &order) {
    if (order.getPrice() != price_) {
        throw std::logic_error("Price mismatch");
    }
    orders_.push_back(order);
}

