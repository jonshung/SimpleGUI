#include "VendingMachine.h"

/**
 * @brief Construct a new Vending Machine:: Vending Machine object, adding a Default page to load.
 * 
 */
VendingMachine::VendingMachine() {
    //this->_lang = ConfigManager("VendingMachine/us.json");
    //this->_style = ConfigManager("style.json");
    std::shared_ptr<Page> pPtr(std::make_shared<Page>());
    VendingMachine::populateDefaultPage(pPtr);
    this->setDirectTarget(pPtr);
    this->loadPage();

    this->_orderHandler = UserOrder();
}

void VendingMachine::render(Page page) {
    MenuManager::render();
}

/**
 * @brief Intitiate a Default Page object
 * 
 */
void VendingMachine::populateDefaultPage(std::shared_ptr<Page> pPtr) {
    std::vector<Selectable> selectables;
    Page& obj = *(pPtr);
    selectables.push_back(Selectable("1. Snacks", &VendingMachine::directSnacksPage));
    selectables.push_back(Selectable("2. Drinks", &VendingMachine::directDrinksPage));
    selectables.push_back(Selectable("3. Your orders", &VendingMachine::directUserOrderPage));
    selectables.push_back(Selectable("4. Quit", &VendingMachine::initQuit, true));
    obj.reset("Home", selectables);
}

/**
 * @brief Selectable Action to direct (navigate) to Default Page
 * 
 * @param m 
 * @param page 
 */
void VendingMachine::directDefaultPage(MenuManager* m) {
    std::shared_ptr<Page> dest = std::make_shared<Page>();
    VendingMachine::populateDefaultPage(dest);
    m->setDirectTarget(dest);
}

/**
 * @brief Initiate a Snacks Page
 * 
 */
void VendingMachine::populateSnacksPage(std::shared_ptr<Page> pPtr) {
    Page& obj = *(pPtr);
    std::vector<Selectable> selectables;
    selectables.push_back(Selectable("1. Snack 1"));
    selectables.push_back(Selectable("2. Snack 2"));
    selectables.push_back(Selectable("3. Snack 3"));
    selectables.push_back(Selectable("4. Snack 4"));
    Page::setSelectablesActions(selectables, &VendingMachine::requestAddSnackOrder);
    selectables.push_back(Selectable("5. Back", &VendingMachine::directDefaultPage));

    obj.reset("Snacks", selectables);
}

/**
 * @brief Selectable Action to direct (navigate) to Snacks Page
 * 
 * @param m 
 */
void VendingMachine::directSnacksPage(MenuManager* m) {
    std::shared_ptr<Page> dest = std::make_shared<Page>();
    VendingMachine::populateSnacksPage(dest);
    m->setDirectTarget(dest);
}

/**
 * @brief Initiate a Drinks Page
 * 
 * @param m 
 */
void VendingMachine::populateDrinksPage(std::shared_ptr<Page> pPtr) {
    Page& obj = *(pPtr);
    std::vector<Selectable> selectables;
    selectables.push_back(Selectable("1. Drink 1"));
    selectables.push_back(Selectable("2. Drink 2"));
    selectables.push_back(Selectable("3. Drink 3"));
    Page::setSelectablesActions(selectables, &VendingMachine::requestAddDrinkOrder);
    selectables.push_back(Selectable("4. Back", &VendingMachine::directDefaultPage));

    obj.reset("Drinks", selectables);
}

/**
 * @brief Selectable Action to direct (navigate) to Drinks Page
 * 
 * @param m 
 */
void VendingMachine::directDrinksPage(MenuManager* m) {
    std::shared_ptr<Page> dest = std::make_shared<Page>();
    VendingMachine::populateDrinksPage(dest);
    m->setDirectTarget(dest);
}

/**
 * @brief Initiate Product Page, holding current user's orders
 * 
 * @param m 
 */
void VendingMachine::populateUserOrderPage(std::shared_ptr<Page> pPtr) {
    Page& obj = *(pPtr);
    obj.reset("Your Order");
}

/**
 * @brief Selectable Action to direct (navigate) to Product Page
 * 
 * @param m 
 */
void VendingMachine::directUserOrderPage(MenuManager* m) {
    VendingMachine *menuHandler = dynamic_cast<VendingMachine*>(m);
    if(menuHandler == NULL) {
        throw std::invalid_argument(concatenateString({"Invalid casting from ", typeid(m).name(), " to ", typeid(m).name()}));
    }
    //  Todo: implement Selectable Action to delete order
    std::shared_ptr<Page> pPtr = std::make_shared<Page>();
    VendingMachine::populateUserOrderPage(pPtr);
    Page& page = *(pPtr);
    int k = 0;
    for(int i : menuHandler->userOrderHandler().getOrders()) {
        page.addSelectable(Selectable(concatenateString({"[", std::to_string(k + 1), "] ", UserOrder::getProductNameFromId(i)})));
        k++;
    }
    page.addSelectable(Selectable("4. Back", &VendingMachine::directDefaultPage));
    page.setInitialSelection(k);
    m->setDirectTarget(pPtr);
}

/**
 * @brief Handling Selectable Action for requesting Vending Machine's User Order Handler to add a snack order
 * 
 * @param m 
 */
void VendingMachine::requestAddSnackOrder(MenuManager* m) {
    VendingMachine* menuHandler = VendingMachine::linker<VendingMachine>(m);
    (menuHandler->userOrderHandler()).addOrder(menuHandler->currentSelection());
    menuHandler->IOHandler()->print("\nAdded order successfully! Press any character to continue...", { "10" });
    m->IOHandler()->getChar();
}

/**
 * @brief Handling Selectable Action for requesting Vending Machine's User Order Handler to add a drink order
 * 
 * @param m 
 */
void VendingMachine::requestAddDrinkOrder(MenuManager* m) {
    VendingMachine* menuHandler = VendingMachine::linker<VendingMachine>(m);
    (menuHandler->userOrderHandler()).addOrder(4 + menuHandler->currentSelection());                // Hard coded for example
    menuHandler->IOHandler()->print("\nAdded order successfully! Press any character to continue...", { "10" });
    m->IOHandler()->getChar();
}

/**
 * @brief Return dynamically safe downcast of MenuManager Object to Vending Machine Object
 * 
 * @tparam T
 * @param m 
 * @return T* 
 */
template<typename T>
T* VendingMachine::linker(MenuManager * m) {
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
 */
void VendingMachine::input(MenuManager* m) {
    std::string buffer;
    std::cout << "\n> ";
    std::getline(std::cin, buffer);
}