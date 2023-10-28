#pragma once
#define _LOCALIZE_CONFIG_

#include "Config.h"
#include <map>
#include <utility>

class LocalizeConfig : ConfigManager {
private:
	std::map<std::string, std::string> _locale;
public:
	const static std::string const _baseLocale[];
	LocalizeConfig(std::string);
	void initialize();
	std::string get(std::string);
};

// that's a pretty long name
const std::string const LocalizeConfig::_baseLocale[] = {
	"quitMessage"
};