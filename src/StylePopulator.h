#pragma once

#include "json.hpp"

using namespace nlohmann;

namespace StylePopulator {
    static ordered_json getDefaultPopulator() {
        std::string input = 
        "{\n"
        "    \"defaultTextColor\": 15,\n"
        "    \"defaultBackgroundColor\": 0,\n"
        "    \"titleColor\":  \"10\",\n"
        "    \"selectingColor\": \"226\"\n"
        "}";
        ordered_json ret;
        try {
            ret = json::parse(input);
        }
        catch (const json::parse_error& ex) {
            std::cout << ex.what() << std::endl;
        }
        return ret;
    }
}