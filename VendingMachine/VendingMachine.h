#pragma once
#define _VENDING_MACHINE_

#include "MenuManager.h"
#include "UserOrderHandler.h"
#include "Config.h"

class VendingMachine : public MenuManager {
private:
    UserOrder _orderHandler;
public:
    void populateDefaultPage(std::shared_ptr<Page>);
    void populateSnacksPage(std::shared_ptr<Page>);
    void populateDrinksPage(std::shared_ptr<Page>);
    void populateUserOrderPage(std::shared_ptr<Page>);

    // ActionType components
    static void directDefaultPage(MenuManager* m);
    static void directSnacksPage(MenuManager* m);
    static void directDrinksPage(MenuManager* m);
    static void directUserOrderPage(MenuManager* m);
    static void doNothing(MenuManager*m);
    static void input(MenuManager* m);

    VendingMachine();
    static VendingMachine* linker(MenuManager *);

    //example render overload
    void render(Page page);

    UserOrder& userOrderHandler() { return _orderHandler; }
    static void requestAddSnackOrder(MenuManager* m);
    static void requestAddDrinkOrder(MenuManager* m);
};