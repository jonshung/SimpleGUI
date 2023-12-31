#include "VendingMachine.h"

/**
 * @brief Construct a new Vending Machine:: Vending Machine object, adding a Default page to load.
 * 
 */
VendingMachine::VendingMachine() {
    _lang = LocalizeConfig("config/us.json", LocalePopulator::getDefaultPopulator()); // overriding default language config
    _stockHandler = StockHandler(".VMStock.json");
    this->_orderHandler = UserOrder();
}

void VendingMachine::render(Page page) {
    MenuManager::render();
}

std::shared_ptr<VendingMachine> VendingMachine::getInstance() {
    if(!_instance) {
        _instance = std::shared_ptr<VendingMachine>(new VendingMachine());
        return _instance;
    }
    return _instance;
}

/**
 * @brief Selectable Action to direct (navigate) to Default Page
 * 
 * @param m 
 * @param page 
 */
void VendingMachine::directDefaultPage(MenuManager* m) {
    VendingMachine* menuHandler = VendingMachine::linker(m);
    if (menuHandler == NULL) {
        throw std::runtime_error(concatenateString({ "Invalid casting from ", typeid(m).name(), " to ", typeid(m).name() }));
    }
    std::shared_ptr<Page> dest = PageProvider::getPage(PageList::DEFAULT);
    m->setDirectTarget(dest);
}

/**
 * @brief Selectable Action to direct (navigate) to Snacks Page
 * 
 * @param m 
 */
void VendingMachine::directSnacksPage(MenuManager* m) {
    VendingMachine* menuHandler = VendingMachine::linker(m);
    if (menuHandler == NULL) {
        throw std::runtime_error(concatenateString({ "Invalid casting from ", typeid(m).name(), " to ", typeid(m).name() }));
    }
    std::shared_ptr<Page> dest = PageProvider::getPage(PageList::SNACKS);
    m->setDirectTarget(dest);
}

/**
 * @brief Selectable Action to direct (navigate) to Drinks Page
 * 
 * @param m 
 */
void VendingMachine::directDrinksPage(MenuManager* m) {
    VendingMachine* menuHandler = VendingMachine::linker(m);
    if (menuHandler == NULL) {
        throw std::runtime_error(concatenateString({ "Invalid casting from ", typeid(m).name(), " to ", typeid(m).name() }));
    }
    std::shared_ptr<Page> dest = PageProvider::getPage(PageList::DRINKS);
    m->setDirectTarget(dest);
}


/**
 * @brief Selectable Action to direct (navigate) to Product Page
 * 
 *  Since this page is dynamically updated, it should be re-render each time a navigation is directed here
 * 
 * @param m 
 */
void VendingMachine::directUserOrderPage(MenuManager* m) {
    std::shared_ptr<Page> dest = PageProvider::getPage(PageList::USERORDER);
    m->setDirectTarget(dest);
}

/**
 * @brief Handling Selectable Action for requesting Vending Machine's User Order Handler to add a snack order
 * 
 * @param m 
 */
void VendingMachine::requestAddSnackOrder(MenuManager* m) {
    VendingMachine* menuHandler = VendingMachine::linker(m);
    Selectable curr = m->getCurrentPage()->getSelectable(menuHandler->currentSelection());
    (menuHandler->userOrderHandler()).addOrder(std::make_shared<SnackType>(curr.data()));
    menuHandler->IOHandler()->print(menuHandler->getLang().get("actionAddOrderSuccess"), {"10"});
    m->IOHandler()->getChar();
}

/**
 * @brief Handling Selectable Action for requesting Vending Machine's User Order Handler to add a drink order
 * 
 * @param m 
 */
void VendingMachine::requestAddDrinkOrder(MenuManager* m) {
    VendingMachine* menuHandler = VendingMachine::linker(m);
    Selectable curr = m->getCurrentPage()->getSelectable(menuHandler->currentSelection());
    (menuHandler->userOrderHandler()).addOrder(std::make_shared<DrinkType>(curr.data()));
    menuHandler->IOHandler()->print(menuHandler->getLang().get("actionAddOrderSuccess"), { "10" });
    m->IOHandler()->getChar();
}


StockHandler& VendingMachine::stockHandler() {
    return _stockHandler;
}

/**
 * @brief Return dynamically safe downcast of MenuManager Object to Vending Machine Object
 * 
 * @param m 
 * @return 
 */
VendingMachine* VendingMachine::linker(MenuManager * m) {
    VendingMachine *menuHandler = dynamic_cast<VendingMachine*>(m);
    if(menuHandler == nullptr) {
        throw std::invalid_argument(concatenateString({"Invalid casting from ", typeid(m).name(), " to VendingMachine*"}));
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