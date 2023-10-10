#include "VendingMachine.h"

/**
 * @brief Construct a new Vending Machine:: Vending Machine object, adding a Default page to load.
 * 
 */
VendingMachine::VendingMachine() {
    this->loadPage(VendingMachine::initDefaultPage());
}

/**
 * @brief Intitiate a Default Page object
 * 
 * @return Page 
 */
Page VendingMachine::initDefaultPage() {
    vector<Selectable> selectables;
    selectables.push_back(Selectable("1. Snacks", &VendingMachine::directSnacksPage));
    selectables.push_back(Selectable("2. Drinks", &VendingMachine::doNothing));
    selectables.push_back(Selectable("3. Quit", &VendingMachine::initQuit));

    Page defaultPage("Home", selectables);
    return defaultPage;
}

/**
 * @brief Selectable Action to direct (navigate) to Default Page
 * 
 * @param m 
 * @param page 
 */
void VendingMachine::directDefaultPage(Menu* m, Page &page) {
    try {
        m->setSelection(page, 0);
    } catch (const std::invalid_argument& e) {
        cout << e.what() << endl;
    }
    page = VendingMachine::initDefaultPage();
    m->setDirect(true);
}

/**
 * @brief Initiate a Snacks Page
 * 
 * @return Page 
 */
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

/**
 * @brief Selectable Action to direct (navigate) to Snacks Page
 * 
 * @param m 
 * @param page 
 */
void VendingMachine::directSnacksPage(Menu* m, Page &page) {
    try {
        m->setSelection(page, 0);
    } catch (const std::invalid_argument& e) {
        cout << e.what() << endl;
    }
    page = VendingMachine::initSnacksPage();
    m->setDirect(true);
}

/**
 * @brief Initiate a Drinks Page
 * 
 * @param m 
 * @param page 
 */
Page VendingMachine::initDrinksPage() {
    Page drinksPage("Drinks");
    return drinksPage;
}

/**
 * @brief Selectable Action to direct (navigate) to Drinks Page
 * 
 * @param m 
 * @param page 
 */
void VendingMachine::directDrinksPage(Menu* m, Page &page) {
    try {
        m->setSelection(page, 0);
    } catch (const std::invalid_argument& e) {
        cout << e.what() << endl;
    }
    m->setDirect(true);
}

/**
 * @brief Initiate Product Page, holding current user's orders
 * @todo: finish this example
 * 
 * @param m 
 * @param page 
 */
Page VendingMachine::initProductPage() {
    Page productPage("Product");
    return productPage;
}

/**
 * @brief Selectable Action to direct (navigate) to Product Page
 * 
 * @param m 
 * @param page 
 */
void VendingMachine::directProductPage(Menu* m, Page &page) {
    try {
        m->setSelection(page, 0);
    } catch (const std::invalid_argument& e) {
        cout << e.what() << endl;
    }
    m->setDirect(true);
}

/**
 * @brief Selectable Action, An example on how to take string input after pressing Selectable
 * @todo: finish this example
 * 
 * @param m 
 * @param page 
 */
void VendingMachine::input(Menu* m, Page &page) {
    std::string buffer;
    std::cout << "\n> ";
    std::getline(std::cin, buffer);
}