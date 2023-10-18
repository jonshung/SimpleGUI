#pragma once
#define _VENDING_MACHINE_

#include "MenuManager.h"
#include "UserOrderHandler.h"
#include "Config.h"

class VendingMachine : public MenuManager {
private:
    UserOrder _orderHandler;
public:
    static Page initDefaultPage();
    static Page initSnacksPage();
    static Page initDrinksPage();
    static Page initUserOrderPage();

    static void directDefaultPage(MenuManager* m, Page &page);
    static void directSnacksPage(MenuManager* m, Page &page);
    static void directDrinksPage(MenuManager* m, Page &page);
    static void directUserOrderPage(MenuManager* m, Page &page);
    static void doNothing(MenuManager*m, Page &page);
    static void input(MenuManager* m, Page &page);

    VendingMachine();
    template<typename T>
    static T* linker(MenuManager *);

    //example render overload
    void render(Page page);

    UserOrder& userOrderHandler() { return _orderHandler; }
    static void requestAddSnackOrder(MenuManager* m, Page &page);
    static void requestAddDrinkOrder(MenuManager* m, Page &page);
};