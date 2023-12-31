#pragma once
#define _DEFAULT_PAGE_H_

#include "Page.h"
#include "VendingMachine.h"

class DefaultPage : public Page {
public:
    inline DefaultPage() {
        std::vector<Selectable> selectables;
        selectables.push_back(Selectable("1. Snacks", &VendingMachine::directSnacksPage));
        selectables.push_back(Selectable("2. Drinks", &VendingMachine::directDrinksPage));
        selectables.push_back(Selectable("3. Your orders", &VendingMachine::directUserOrderPage));
        selectables.push_back(Selectable("4. Quit", &VendingMachine::initQuit, true));
        reset(VendingMachine::_lang.get("homeTitle"), selectables);
    }
};