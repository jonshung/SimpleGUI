#pragma once
#define _LOCALIZE_CONFIG_

#include "Config.h"
#include <map>
#include <utility>

class LocalizeConfig : public ConfigManager {
private:
	std::map<std::string, std::string> _locale;
	inline static std::string _baseLocale[] = {
	"quitMessage"
	};
public:
	LocalizeConfig(std::string, json = json());
	LocalizeConfig();
	void initialize();
	std::string get(std::string);
};