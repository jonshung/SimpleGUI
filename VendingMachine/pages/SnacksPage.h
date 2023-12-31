#pragma once
#define _SNACKS_PAGE_H_

#include "Page.h"
#include "VendingMachine.h"

class SnacksPage : public Page {
public:

    /**
     * @brief Initiate a Snacks Page
     *
     */
    inline SnacksPage() {
        std::vector<Selectable> selectables;
        int k = 0;
        if (VendingMachine::stockHandler().stocks()["snacks"].is_array()) {
            std::vector stockList = VendingMachine::stockHandler().stocks()["snacks"].get<std::vector<std::string>>();
            for (k; k < VendingMachine::stockHandler().stocks()["snacks"].size(); ++k) {
                Selectable ss(std::to_string(k+1) + ". " + stockList[k]);
                ss.data(stockList[k]);
                selectables.push_back(ss);
            }
            Page::setSelectablesActions(selectables, &VendingMachine::requestAddSnackOrder);
        }
        selectables.push_back(Selectable(std::to_string(k+1) + ". Back", &VendingMachine::directDefaultPage));
        reset(VendingMachine::_lang.get("snacksPageTitle"), selectables);
    }
};