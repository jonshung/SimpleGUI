#pragma once
#define _SNACKS_PAGE_H_

#include "Page.h"
#include "VendingMachine.h"

class UserOrderPage : public Page {
public:
    /**
     * @brief Initiate Product Page, holding current user's orders
     *
     * @param m
     */
    inline UserOrderPage() {
        preload();
    }

    inline void preload() override {
        reset(VendingMachine::_lang.get("userOrderPageTitle"));
        std::shared_ptr<VendingMachine> menuHandler = VendingMachine::getInstance();
        int k = 0;
        for (std::shared_ptr<StockType> i : menuHandler->userOrderHandler().getOrders()) {
            addSelectable(Selectable(concatenateString({ "[", std::to_string(k + 1), "] ", i->stock() })));
            k++;
        }
        addSelectable(Selectable(std::to_string(k) + ". Back", &VendingMachine::directDefaultPage));
        setInitialSelection(k);
    }
};