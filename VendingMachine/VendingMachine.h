#pragma once
#define _VENDING_MACHINE_

#include "src/MenuManager.h"
#include "UserOrderHandler.h"
#include "src/utils/Config.h"

class VendingMachine : public Menu {
private:
    UserOrder _orderHandler;
public:
    static Page initDefaultPage();
    static Page initSnacksPage();
    static Page initDrinksPage();
    static Page initUserOrderPage();

    static void directDefaultPage(Menu* m, Page &page);
    static void directSnacksPage(Menu* m, Page &page);
    static void directDrinksPage(Menu* m, Page &page);
    static void directUserOrderPage(Menu* m, Page &page);
    static void doNothing(Menu*m, Page &page);
    static void input(Menu* m, Page &page);

    VendingMachine();
    template<typename T>
    static T* linker(Menu *);

    //example render overload
    void render(Page page);

    UserOrder& userOrderHandler() { return _orderHandler; }
    static void requestAddSnackOrder(Menu* m, Page &page);
    static void requestAddDrinkOrder(Menu* m, Page &page);
};