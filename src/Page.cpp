#include "Page.h"

std::string Page::title() {
    return _title;
}

int Page::initialSelection() {
    return _initialSelection;
}

std::vector<Selectable>& Page::getSelectables() {
    return _selectables;
}

Page::Page(std::string title) {
    _initialSelection = 0;
    _title = title;
}

Page::Page(std::string title, std::vector<Selectable> selectables) {
    _initialSelection = 0;
    _title = title;
    _selectables = selectables;
}

/**
 * @brief Add an item to the page
 *
 * @param selectable
 */
void Page::addSelectable(Selectable selectable) {
    _selectables.push_back(selectable);
}

/**
 * @brief Remove an item from the page, throw exception if the operation failed
 *
 * @param id
 */
void Page::removeItem(int id) {
    if (id >= _selectables.size() || id < 0) {
        std::string msg = concatenateString({ "Exception at removing page item id: ", std::to_string(id),
                                            " at page size: ", std::to_string(_selectables.size()), "\n" });
        throw std::invalid_argument(msg);
    }
    _selectables.erase(_selectables.begin() + id);
}

/**
 * @brief Get a Selectable item, throw exception if the operation failed
 *
 * @param id
 * @return Selectable
 */
Selectable Page::getSelectable(int id) {
    if (id >= _selectables.size() || id < 0) {
        std::string msg = concatenateString({ "Exception at getting page navigator id: ", std::to_string(id),
                                            " from page size: ", std::to_string(_selectables.size()), "\n" });
        throw std::invalid_argument("received negative value");
    }
    return _selectables[id];
}

/**
 * @brief Set all selection in a given std::vector to a Selectable Action
 *
 * @param list
 * @param action
 */
void Page::setSelectablesActions(std::vector<Selectable>& list, ActionType action) {
    for (Selectable& i : list) i.setAction(action);
}

/**
 * @brief Safely set the initial selection of the page based on size constraint
 *
 * @param id
 */
void Page::setInitialSelection(int id) {
    if (id >= this->getSelectables().size()) {
        std::string msg = concatenateString({ "Incorrect Initial selection value of ", std::to_string(id),
                                            " in page size: ", std::to_string(this->getSelectables().size()) });
        throw std::invalid_argument(msg);
    }
    _initialSelection = id;
}