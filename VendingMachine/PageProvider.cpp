#include "PageProvider.h"

std::shared_ptr<Page> PageProvider::getPage(int idx) {
    if (idx >= _pages.size()) {
        _pages.resize(std::max<int>(idx + 1, _pages.size()));
    }
    switch (idx) {
    case PageList::USERORDER: {
        if (!_pages[idx]) {
            std::cout << "make\n";
            _pages[idx] = std::make_shared<UserOrderPage>();
        }
        break;
    }
    case PageList::SNACKS: {
        if (!_pages[idx]) {
            _pages[idx] = std::make_shared<SnacksPage>();
        }
        break;
    }
    case PageList::DRINKS: {
        if (!_pages[idx]) {
            _pages[idx] = std::make_shared<DrinksPage>();
        }
        break;
    }
    case PageList::DEFAULT:
    default: {
        if (!_pages[idx]) {
            _pages[idx] = std::make_shared<DefaultPage>();
        }
        break;
    }
    }
    return _pages[idx];
}