#pragma once
#define _SELECTABLE_BASE_

#include <string>
#include "MenuManager.h"
#include <memory>

class SelectableAction;
class MenuManager;
class Page;

typedef void (*ActionType)(MenuManager*);

class Selectable {
private:
    std::string _label;
    std::shared_ptr<SelectableAction> _actionPtr;
public:
    std::string label();
    std::shared_ptr<SelectableAction> getAction();
    void setAction(ActionType, bool = false);
    Selectable(std::string, ActionType, bool = false);
    Selectable(std::string);
    Selectable();
};

class SelectableAction {
private:
    ActionType _actionModule;
    bool _isQuit;
public:
    bool isQuit();
    SelectableAction();
    SelectableAction(ActionType, bool = false);
    ActionType getModule();
};