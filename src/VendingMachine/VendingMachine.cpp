#include "VendingMachine.h"

VendingMachine::VendingMachine() {
    this->loadPage(VendingMachine::initDefaultPage());
}

Page VendingMachine::initDefaultPage() {
    vector<Selectable> selectables;
    selectables.push_back(Selectable("1. Snacks", &VendingMachine::directSnacksPage));
    selectables.push_back(Selectable("2. Drinks", &VendingMachine::doNothing));
    selectables.push_back(Selectable("3. Quit", &VendingMachine::initQuit));

    Page defaultPage("Home", selectables);
    return defaultPage;
}

void VendingMachine::directDefaultPage(Menu* m, Page &page) {
    try {
        m->setSelection(page, 0);
    } catch (const std::invalid_argument& e) {
        cout << e.what() << endl;
    }
    page = VendingMachine::initDefaultPage();
    m->setDirect(true);
}

Page VendingMachine::initSnacksPage() {
    vector<Selectable> selectables;
    selectables.push_back(Selectable("1. Snack 1"));
    selectables.push_back(Selectable("2. Snack 2"));
    selectables.push_back(Selectable("3. Snack 3"));
    selectables.push_back(Selectable("4. Snack 4"));
    Page::doNothingVector(selectables);
    selectables[0].setAction(&VendingMachine::input);

    selectables.push_back(Selectable("5. Back", &VendingMachine::directDefaultPage));

    Page snacksPage("Snacks", selectables);
    return snacksPage;
}

void VendingMachine::directSnacksPage(Menu* m, Page &page) {
    try {
        m->setSelection(page, 0);
    } catch (const std::invalid_argument& e) {
        cout << e.what() << endl;
    }
    page = VendingMachine::initSnacksPage();
    m->setDirect(true);
}

void VendingMachine::directDrinksPage(Menu* m, Page &page) {
    try {
        m->setSelection(page, 0);
    } catch (const std::invalid_argument& e) {
        cout << e.what() << endl;
    }
    m->setDirect(true);
}

void VendingMachine::directProductPage(Menu* m, Page &page) {
    try {
        m->setSelection(page, 0);
    } catch (const std::invalid_argument& e) {
        cout << e.what() << endl;
    }
    m->setDirect(true);
}

void VendingMachine::input(Menu* m, Page &page) {
    std::string buffer;
    std::cout << "\n> ";
    std::getline(std::cin, buffer);
}

Page VendingMachine::initDrinksPage() {
    Page drinksPage("Drinks");
    return drinksPage;
}

Page VendingMachine::initProductPage() {
    Page productPage("Product");
    return productPage;
}
