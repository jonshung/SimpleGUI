#include <iostream>
#include "VendingMachine.h"

int main() {
    std::cout << "Vending Machine V1.0\n\n";
    std::shared_ptr<VendingMachine> menuHandler = VendingMachine::getInstance();
    std::shared_ptr<Page> defaultPage = PageProvider::getPage(PageList::DEFAULT);
    menuHandler->setDirectTarget(defaultPage);
    menuHandler->loadPage();
    return 0;
}