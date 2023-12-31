#include "Selectable.h"

/**
 * @brief Return the displaying selectable label
 * @return
*/
std::string Selectable::label() {
    return _label;
}

/**
 * @brief Return the embedded data of this selectable object
 * @return
*/
std::string Selectable::data() {
    return _data;
}

/**
 * @brief Set the embedded data
 * @return
*/
void Selectable::data(std::string vl) {
    _data = vl;
}

/**
 * @brief return a pointer to a SelectableAction object
 * @return
*/
std::shared_ptr<SelectableAction> Selectable::getAction() {
    return _actionPtr;
}

/**
 * @brief Set this selectable action with a function-pointer to the target module (namely the ActionType type)
 * @param action 
 * @param isQuit 
*/
void Selectable::setAction(ActionType action, bool isQuit) {
    _actionPtr = std::make_shared<SelectableAction>(action, isQuit);
}

/**
 * @brief Passing ActionType pointer should check whether it matches type definition in header file.
 * @param label 
 * @param action 
 * @param isQuit 
*/
Selectable::Selectable(std::string label, ActionType action, bool isQuit) {
    _label = label;
    _actionPtr = std::make_shared<SelectableAction>(action, isQuit);
}

/**
 * @param label 
*/
Selectable::Selectable(std::string label) {
    _label = label;
    _actionPtr = nullptr;
}

/**
 * @brief Empty creation of the selectable object
*/
Selectable::Selectable() {
    _label = "";
    _actionPtr = nullptr;
}

/**
 * @brief Empty creation of the SelectableAction component
*/
SelectableAction::SelectableAction() {
    _actionModule = nullptr;
    _isQuit = false;
}

/**
 * @brief Passing ActionType pointer should check whether it matches type definition in header file.
 * @param actionModule 
 * @param quit 
*/
SelectableAction::SelectableAction(ActionType actionModule, bool quit) {
    _actionModule = actionModule;
    _isQuit = quit;
}

/**
 * @brief Check if current selection is a quit command, will be deprecated in the near future through
 *        Multi threading event handler
 * @return 
*/
bool SelectableAction::isQuit() {
    return _isQuit;
}

/**
 * @brief Get the action module associate with this SelectableAction
 * @return 
*/
ActionType SelectableAction::getModule() {
    return _actionModule;
}