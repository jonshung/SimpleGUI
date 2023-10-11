#include "VendingMachine.h"

/**
 * @brief Construct a new Vending Machine:: Vending Machine object, adding a Default page to load.
 * 
 */
VendingMachine::VendingMachine() {
    this->loadPage(VendingMachine::initDefaultPage());
    _orderHandler = UserOrder();
}

void VendingMachine::render(Page page) {
    this->print("Brought to you by Kiet Hung!", Color::NAVY);
    Menu::render(page);
}

/**
 * @brief Intitiate a Default Page object
 * 
 * @return Page 
 */
Page VendingMachine::initDefaultPage() {
    vector<Selectable> selectables;
    selectables.push_back(Selectable("1. Snacks", &VendingMachine::directSnacksPage));
    selectables.push_back(Selectable("2. Drinks", &VendingMachine::directDrinksPage));
    selectables.push_back(Selectable("4. Your orders", &VendingMachine::directUserOrderPage));
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
    Page::setSelectablesActions(selectables, &VendingMachine::requestAddSnackOrder);
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
    vector<Selectable> selectables;
    selectables.push_back(Selectable("1. Drink 1"));
    selectables.push_back(Selectable("2. Drink 2"));
    selectables.push_back(Selectable("3. Drink 3"));
    Page::setSelectablesActions(selectables, &VendingMachine::requestAddDrinkOrder);
    selectables.push_back(Selectable("4. Back", &VendingMachine::directDefaultPage));

    Page drinksPage("Drinks", selectables);
    return drinksPage;
}

/**
 * @brief Selectable Action to direct (navigate) to Drinks Page
 * 
 * @param m 
 * @param page 
 */
void VendingMachine::directDrinksPage(Menu* m, Page &page) {
    page = VendingMachine::initDrinksPage();
    m->setDirect(true);
}

/**
 * @brief Initiate Product Page, holding current user's orders
 * @todo: finish this example
 * 
 * @param m 
 * @param page 
 */
Page VendingMachine::initUserOrderPage() {
    Page productPage("Your Order");
    return productPage;
}

/**
 * @brief Selectable Action to direct (navigate) to Product Page
 * 
 * @param m 
 * @param page 
 */
void VendingMachine::directUserOrderPage(Menu* m, Page &page) {
    VendingMachine *menuHandler = dynamic_cast<VendingMachine*>(m);
    if(menuHandler == NULL) {
        throw std::invalid_argument(concatenateString({"Invalid casting from ", typeid(m).name(), " to ", typeid(m).name()}));
    }
    //  Todo: implement Selectable Action to delete order
    page = VendingMachine::initUserOrderPage();
    int k = 0;
    for(int i : menuHandler->userOrderHandler().getOrders()) {
        page.addSelectable(Selectable(concatenateString({"[", std::to_string(k + 1), "] ", UserOrder::getProductNameFromId(i)})));
        k++;
    }
    page.addSelectable(Selectable("4. Back", &VendingMachine::directDefaultPage));
    page.setInitialSelection(k);
    m->setDirect(true);
}

/**
 * @brief Handling Selectable Action for requesting Vending Machine's User Order Handler to add a snack order
 * 
 * @param m 
 * @param page 
 */
void VendingMachine::requestAddSnackOrder(Menu* m, Page &page) {
    VendingMachine* menuHandler = VendingMachine::linker<VendingMachine>(m);
    (menuHandler->userOrderHandler()).addOrder(menuHandler->currentSelection());
    menuHandler->print("\nAdded order successfully! Press any character to continue...", Color::GREEN);
    _getch();
}

/**
 * @brief Handling Selectable Action for requesting Vending Machine's User Order Handler to add a drink order
 * 
 * @param m 
 * @param page 
 */
void VendingMachine::requestAddDrinkOrder(Menu* m, Page &page) {
    VendingMachine* menuHandler = VendingMachine::linker<VendingMachine>(m);
    (menuHandler->userOrderHandler()).addOrder(4 + menuHandler->currentSelection());                // Hard coded for example
    menuHandler->print("\nAdded order successfully! Press any character to continue...", Color::GREEN);
    _getch();
}

/**
 * @brief Return dynamically safe downcast of Menu Object to Vending Machine Object
 * 
 * @tparam T
 * @param m 
 * @return T* 
 */
template<typename T>
T* VendingMachine::linker(Menu * m) {
    VendingMachine *menuHandler = dynamic_cast<VendingMachine*>(m);
    if(menuHandler == NULL) {
        throw std::invalid_argument(concatenateString({"Invalid casting from ", typeid(m).name(), " to ", typeid(m).name()}));
    }
    return menuHandler;
}

/**
 * @brief Selectable Action, An example on how to take string input after pressing Selectable
 * @todo: finish this example
 * 
 * @note Unused
 * 
 * @param m 
 * @param page 
 */
void VendingMachine::input(Menu* m, Page &page) {
    std::string buffer;
    std::cout << "\n> ";
    std::getline(std::cin, buffer);
}