#pragma once
#define _VENDING_MACHINE_

#include "MenuManager.h"

class VendingMachine : public Menu {
public:
    static Selectable initDefaultPage(Menu* m);
    static Selectable initSnacksPage(Menu* m);
    static Selectable initDrinksPage(Menu* m);
    static Selectable initProductPage(Menu* m);
    VendingMachine() {
        this->loadPage(initDefaultPage(this));
    }
};