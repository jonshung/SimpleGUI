#pragma once
#define _VENDING_MACHINE_

#include "MenuManager.h"
#include "UserOrderHandler.h"
#include "Config.h"
#include "StockHandler.h"
#include "SnackType.h"
#include "DrinkType.h"

#include "LocalePopulator.h"

class VendingMachine : public MenuManager {
private:
    UserOrder _orderHandler;
    inline static std::shared_ptr<VendingMachine> _instance = nullptr;
    inline static StockHandler _stockHandler;
    VendingMachine();
public:
    static std::shared_ptr<VendingMachine> getInstance();
    static StockHandler& stockHandler();

    // ActionType components
    static void directDefaultPage(MenuManager* m);
    static void directSnacksPage(MenuManager* m);
    static void directDrinksPage(MenuManager* m);
    static void directUserOrderPage(MenuManager* m);
    static void input(MenuManager* m);

    static VendingMachine* linker(MenuManager *);

    //example render overload
    void render(Page page);

    UserOrder& userOrderHandler() { return _orderHandler; }
    static void requestAddSnackOrder(MenuManager* m);
    static void requestAddDrinkOrder(MenuManager* m);
};

#include "PageProvider.h"