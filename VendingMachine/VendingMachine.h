#pragma once
#define _VENDING_MACHINE_

#include "MenuManager.h"
#include "UserOrderHandler.h"
#include "Config.h"

class VendingMachine : public MenuManager {
private:
    UserOrder _orderHandler;
public:
    static void populateDefaultPage(std::shared_ptr<Page>);
    static void populateSnacksPage(std::shared_ptr<Page>);
    static void populateDrinksPage(std::shared_ptr<Page>);
    static void populateUserOrderPage(std::shared_ptr<Page>);

    static void directDefaultPage(MenuManager* m);
    static void directSnacksPage(MenuManager* m);
    static void directDrinksPage(MenuManager* m);
    static void directUserOrderPage(MenuManager* m);
    static void doNothing(MenuManager*m);
    static void input(MenuManager* m);

    VendingMachine();
    template<typename T>
    static T* linker(MenuManager *);

    //example render overload
    void render(Page page);

    UserOrder& userOrderHandler() { return _orderHandler; }
    static void requestAddSnackOrder(MenuManager* m);
    static void requestAddDrinkOrder(MenuManager* m);
};