#pragma once

#include "json.hpp"

using namespace nlohmann;

namespace LocalePopulator {
    static ordered_json getDefaultPopulator() {
        ordered_json ret;
        ret["quitMessage"] = "Quitting program...";
        ret["homeTitle"] = "Home";
        ret["snacksPageTitle"] = "Snacks";
        ret["drinksPageTitle"] = "Drinks";
        ret["userOrderPageTitle"] = "Your Order";
        ret["actionAddOrderSuccess"] = "\nAdded order successfully! Press any character to continue...";
        return ret;
    }
}