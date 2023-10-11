#include "MenuManager.h"

/**
 * @brief Construct a new Menu:: Menu object
 * 
 */
Menu::Menu() {
    _direct = false;
    _WindowsHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    _bgColor = Color::BLACK;
    _defaultTextColor = Color::WHITE;
    _currentSelection = 0;
}

/**
 * @brief Set current text color
 * 
 * @param colorId 
 */
void Menu::setColor(int colorId) {
    HANDLE WindowsHandler = this->_WindowsHandle;
    int colorOffset = getTextColor(colorId, this->bgColor());
    SetConsoleTextAttribute(WindowsHandler, colorId);
}

/**
 * @brief Print a string to screen and add a newline character at the end
 * 
 * @param prompt 
 * @param color 
 */
void Menu::print(string prompt, int color) {
    this->setColor(color);
    cout << prompt << endl;
    this->setColor(this->defaultTextColor());
}

/**
 * @brief Page loading pipeline (Do not overload)
 * 
 * @param page 
 */
void Menu::loadPage(Page page) {
    this->preloadPage(page);
    this->render(page);
    this->postLoadPage(page);
}

void Menu::preloadPage(Page page) {
    clearScreen();
}

/**
 * @brief Standard procedure to render a page, throw an exception if the number of displaying items is not equal to the number of selectables
 * 
 * @param page 
 */
void Menu::render(Page page) {
    vector<Selectable> selectables = page.getSelectables();
    if(this->direct()) {
        this->forceSetSelection(page.initialSelection());
        this->setDirect(false);
    }
    this->print(page.title(), Color::GREEN);
    this->print("");
    for (int i = 0; i < selectables.size(); i++) {
        if (this->currentSelection() == i) this->print(selectables[i].label(), Color::PALE_YELLOW);
        else this->print(selectables[i].label(), this->defaultTextColor());
    }
}

/**
 * @brief Handle event listening constructor
 * 
 * @param page 
 */
void Menu::postLoadPage(Page page) {
    this->eventListener(page);
}

/**
 * @brief Handle user inputs in the interface.
 * @todo: SEPERATING EVENT HANDLING INTO METHODS
 *
 * @param page
 */
void Menu::eventListener(Page page) {
    bool updateFlag = false;
    bool quitFlag = false;
    while (true) {
        if (updateFlag) break;
        unsigned char key = _getch();
        if (Keys::Arrow == key) {
            unsigned char arrow = _getch();
            int selection = this->currentSelection();
            switch (arrow) {
            case Keys::Up: {
                while (selection > 0) {
                    --selection;
                    Selectable dest;
                    try {
                        dest = page.getSelectable(selection);
                    } catch(const std::invalid_argument& e) {
                        cout << e.what() << endl;
                    }
                    if (dest.getAction() != nullptr) {
                        this->setSelection(page, selection);
                        updateFlag = true;
                        break;
                    }
                }
                break;
            }
            case Keys::Down: {
                while (selection < page.getSelectables().size() - 1) {
                    ++selection;
                    Selectable dest;
                    try {
                        dest = page.getSelectable(selection);
                    } catch(const std::invalid_argument& e) {
                        cout << e.what() << endl;
                    }
                    if (dest.getAction() != nullptr) {
                        this->setSelection(page, selection);
                        updateFlag = true;
                        break;
                    }
                }
                break;
            }
            default: break;
            }
        }
        if (Keys::Enter == key) {
            Selectable dest = page.getSelectable(this->currentSelection());
            if (dest.getAction() == nullptr) continue;
            if (dest.getAction() == (void*) &initQuit) {
                quitFlag = true;
                break;
            }

            try {
                (dest.getAction())(this, page);
            } catch(const std::invalid_argument& e) {
                this->print(e.what(), Color::RED);
            }
            updateFlag = true;
        }
        if (updateFlag) break;
    }
    if (!quitFlag) loadPage(page);
}

/**
 * @brief Get default menu color
 * 
 * @param color 
 */
void Menu::setDefaultTextColor(int color) {
    this->_defaultTextColor = color;
}

/**
 * @brief Set current user's selection, throw an exception if the selection cannot be found
 * 
 * @param page 
 * @param id 
 */
void Menu::setSelection(Page page, int id) {
    if (id >= page.getSelectables().size()) {
        string msg = concatenateString({ "Exception at trying to select navigator ", std::to_string(id), " in page navigator size: ", std::to_string(page.getSelectables().size()), "\n" });
        this->print(msg, Color::RED);
        return;
    }
    this->_currentSelection = id;
}

/**
 * @brief This should only be used when we are certain the selection is available
 * 
 * @param id 
 */
void Menu::forceSetSelection(int id) {
    this->_currentSelection = id;
}

/**
 * @brief Default quitting action
 */
void Menu::initQuit(Menu* m, Page &page) {
    m->print("Quitting program...", Color::GRAY);
}

/**
 * @brief This function is a placeholder for selectable that doesn't have any action
 */
void Menu::doNothing(Menu* m, Page &page) {
}

string Menu::getMenuName() {
    return _menuName;
}

/**
 * @brief Do no cast since this is the base class
 * 
 * @tparam T
 * @param m 
 * @return T*
 */
template<typename T>
T* Menu::linker(Menu *m) {
    return m;
}

// Class page
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
        string msg = concatenateString({ "Exception at removing page item id: ", std::to_string(id), " at page size: ", std::to_string(_selectables.size()), "\n" });
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
        string msg = concatenateString({ "Exception at getting page navigator id: ", std::to_string(id), " from page size: ", std::to_string(_selectables.size()), "\n" });
        throw std::invalid_argument( "received negative value" );
    }
    return _selectables[id];
}

void Page::setSelectablesActions(vector<Selectable>& list, SelectableAction action) {
    for(Selectable& i : list) i.setAction(action);
}

void Page::setInitialSelection(int id) {
    if(id >= this->getSelectables().size()) {
        string msg = concatenateString({"Incorrect Initial selection value of ", std::to_string(id), " in page size: ", std::to_string(this->getSelectables().size())});
        throw std::invalid_argument(msg);
    }
    _initialSelection = id;
}