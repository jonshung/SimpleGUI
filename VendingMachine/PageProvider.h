#pragma once

#include "VendingMachine.h"
#include "pages/DefaultPage.h"
#include "pages/DrinksPage.h"
#include "pages/SnacksPage.h"
#include "pages/UserOrderPage.h"

enum PageList {
    DEFAULT = 0,
    SNACKS = 1,
    DRINKS = 2,
    USERORDER = 3
};

namespace PageProvider {
    static std::vector<std::shared_ptr<Page>> _pages;
    std::shared_ptr<Page> getPage(int = PageList::DEFAULT);
}