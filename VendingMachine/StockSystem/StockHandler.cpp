#include "StockHandler.h"

#include <iostream>
StockHandler::StockHandler(std::string filepath) {
    _filepath = filepath;
    if(!std::filesystem::is_regular_file(filepath)) {
        defaultInit();
        save(filepath);
    }
    else {
        std::fstream fileHandler(filepath, std::fstream::in);
        if (!fileHandler.is_open()) {
            defaultInit();
            save(filepath);
            return;
        }
        try {
            _stocks = json::parse(fileHandler);
        }
        catch (const json::parse_error& ex) {
            std::cout << ex.what() << "\n";
            defaultInit();
            save(filepath);
            fileHandler.close();
            return;
        }
        fileHandler.close();
    }
}

void StockHandler::defaultInit() {
    ordered_json defaultConfig;
    defaultConfig["snacks"] = json::array();
    defaultConfig["drinks"] = json::array();
    _stocks = defaultConfig;
}


ordered_json& StockHandler::stocks() {
    return _stocks;
}

void StockHandler::save(std::string filepath) {
    std::fstream fileHandler(filepath, std::fstream::out);
    fileHandler << std::setw(4) << _stocks;
    fileHandler.close();
}

StockHandler::~StockHandler() {
    save(_filepath);
}