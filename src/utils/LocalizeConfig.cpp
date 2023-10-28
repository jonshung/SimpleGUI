#include "LocalizeConfig.h"

/**
 * @brief Load config file and initialize locale resources
 * @param configFile 
*/
LocalizeConfig::LocalizeConfig(std::string configFile) {
	loadFromFile(configFile);
	initialize();
}

/**
 * @brief Default initialization
*/
LocalizeConfig::LocalizeConfig() {
	_locale = std::map<std::string, std::string>();
}

/**
 * @brief Initialize the locale resources and check for base locale availabilty
*/
void LocalizeConfig::initialize() {
	if (_rawData.size() == 0) {
		std::string excptMsg = "Invalid source for locale configuration at: " + _fileName;
		throw std::runtime_error(excptMsg);
	}

	for (const auto& it : _rawData.items()) {
		_locale.insert(std::pair<std::string, std::string>{it.key(), it.value()});
	}

	for (auto it = std::begin(_baseLocale); it != std::end(_baseLocale); it++) {
		if (_locale.find(*it) == _locale.end()) {
			throw std::logic_error("Unable to find base locale " + (*it->c_str()));
		}
	}
}

/**
 * @brief Todo: complete
 * @param  
 * @return 
*/
std::string LocalizeConfig::get(std::string key) {
	if (_locale.find(key) == _locale.end()) return std::string("");
	return _locale.at(key);
}