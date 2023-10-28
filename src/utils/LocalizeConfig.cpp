#include "LocalizeConfig.h"

/**
 * @brief Load config file and initialize locale resources
 * @param configFile 
*/
LocalizeConfig::LocalizeConfig(std::string configFile) {
	loadFromFile(configFile);
}

/**
 * @brief Initialize the locale resources and check for base locale availabilty
*/
void LocalizeConfig::initialize() {
	if (_rawData.size() == 0) {
		const char* cFilename = _fileName.c_str();
		char* excptMsg = "Invalid source for locale configuration at: ";
		strcat(excptMsg, cFilename);
		throw std::exception(excptMsg);
	}
	for (const auto& i : _rawData.items()) {
		_locale.insert(std::pair<std::string, std::string>{i.key(), i.value()});
	}
	for (const auto& i : _locale) {
		if(i.first)
	}
}

/**
 * @brief Todo: complete
 * @param  
 * @return 
*/
std::string LocalizeConfig::get(std::string) {
};