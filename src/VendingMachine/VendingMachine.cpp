#include "VendingMachine.h"

Selectable VendingMachine::initDefaultPage(Menu* m) {
    vector<string> items;
    vector<SelectableNavigator> nav;
    items.push_back("1. Snacks");
    items.push_back("2. Drinks");
    items.push_back("3. Quit");

    nav.push_back(&VendingMachine::initSnacksPage);
    nav.push_back(&VendingMachine::initDrinksPage);
    nav.push_back(&Menu::initQuit);

    Selectable defaultPage(m, "Home", items, nav);
    defaultPage.setPage();
    return defaultPage;
}

Selectable VendingMachine::initSnacksPage(Menu* m) {
    vector<string> items;
    items.push_back("1. Lays");
    items.push_back("2. smth2");
    items.push_back("3. smth3");
    items.push_back("4. smth4");
    items.push_back("5. Back");

    vector<SelectableNavigator> navs(items.size(), &Menu::doNothing);

    navs[4] = &VendingMachine::initDefaultPage;

    Selectable snacksPage(m, "Snacks", items, navs);
    snacksPage.setPage();
    return snacksPage;
}

Selectable VendingMachine::initDrinksPage(Menu* m) {
    Selectable drinksPage("Drinks");
    drinksPage.setPage();
    return drinksPage;
}

Selectable VendingMachine::initProductPage(Menu* m) {
    Selectable productPage(m, "Product");
    productPage.setPage();
    return productPage;
}
