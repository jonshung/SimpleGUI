#pragma once
#define _VENDING_MACHINE_

#include "MenuManager.h"

class VendingMachine : public Menu {
private:
public:
    static Page initDefaultPage();
    static Page initSnacksPage();
    static Page initDrinksPage();
    static Page initProductPage();

    static void directDefaultPage(Menu* m, Page &page);
    static void directSnacksPage(Menu* m, Page &page);
    static void directDrinksPage(Menu* m, Page &page);
    static void directProductPage(Menu* m, Page &page);

    static void input(Menu* m, Page &page);
    VendingMachine();
};