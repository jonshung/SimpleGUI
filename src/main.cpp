#include <iostream>
#include "VendingMachine/VendingMachine.h"

using namespace std;

int main() {
    cout << "Vending Machine V1.0\n\n";
    VendingMachine menuHandler;
    menuHandler.loadPage(VendingMachine::initDefaultPage(&menuHandler));   // We can automate the initial page load by adding a constructor to the menu handler
}