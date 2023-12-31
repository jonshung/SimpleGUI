#pragma once
#define _SNACKS_PAGE_H_

#include "Page.h"
#include "VendingMachine.h"

class DrinksPage : public Page {
public:

    /**
     * @brief Initiate a Drinks Page
     *
     */
    inline DrinksPage() {
        std::vector<Selectable> selectables;
        int k = 0;
        if (VendingMachine::stockHandler().stocks()["drinks"].is_array()) {
            std::vector stockList = VendingMachine::stockHandler().stocks()["drinks"].get<std::vector<std::string>>();
            for (k; k < VendingMachine::stockHandler().stocks()["drinks"].size(); ++k) {
                Selectable ss(std::to_string(k + 1) + ". " + stockList[k]);
                ss.data(stockList[k]);
                selectables.push_back(ss);
            }
            Page::setSelectablesActions(selectables, &VendingMachine::requestAddDrinkOrder);
        }
        selectables.push_back(Selectable(std::to_string(k+1) + ". Back", &VendingMachine::directDefaultPage));
        reset(VendingMachine::_lang.get("drinksPageTitle"), selectables);
    }
};