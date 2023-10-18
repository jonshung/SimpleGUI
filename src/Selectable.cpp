#include "Selectable.h"

std::string Selectable::label() {
    return _label;
}

SelectableAction Selectable::getAction() {
    return *(_actionPtr.get());
}

void Selectable::setAction(ActionType action, bool isQuit) {
    _actionPtr = std::make_shared<SelectableAction>(action, isQuit);
}

Selectable::Selectable(std::string label, ActionType action, bool isQuit) {
    _label = label;
    _actionPtr = std::make_shared<SelectableAction>(action, isQuit);
}

Selectable::Selectable(std::string label) {
    _label = label;
    _actionPtr = nullptr;
}

Selectable::Selectable() {
    _label = "";
    _actionPtr = nullptr;
}

SelectableAction::SelectableAction() {
    _actionModule = nullptr;
    _isQuit = false;
}

SelectableAction::SelectableAction(ActionType actionModule, bool quit) {
    _actionModule = actionModule;
    _isQuit = quit;
}

bool SelectableAction::isQuit() {
    return _isQuit;
}

ActionType SelectableAction::getModule() {
    return _actionModule;
}