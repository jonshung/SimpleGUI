#include "MenuManager.h"

int MenuManager::defaultTextColor() { 
    return _defaultTextColor; 
}

int MenuManager::bgColor() { 
    return _bgColor; 
}

int MenuManager::currentSelection() { 
    return _currentSelection; 
}

bool MenuManager::direct() { 
    return _direct; 
}

void MenuManager::setDirect(bool vl) { 
    _direct = vl; 
}

/**
 * @brief Construct a new MenuManager:: MenuManager object
 *
 */
MenuManager::MenuManager() {
    _direct = false;
    _WindowsHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    _currentSelection = 0;
    this->_lang = ConfigManager("config/us.json");
    this->_style = ConfigManager("config/style.json");

    _bgColor = _style.get<int>("defaultBackgroundColor");
    _bgColor = (_bgColor == -1) ? Color::BLACK : _bgColor;
    _defaultTextColor = _style.get<int>("defaultTextColor");
    _defaultTextColor = (_defaultTextColor == -1) ? Color::WHITE : _defaultTextColor;
}

/**
 * @brief Set current text color
 *
 * @param colorId
 */
void MenuManager::setColor(int colorId) {
    HANDLE WindowsHandler = this->_WindowsHandle;
    int colorOffset = getTextColor(colorId, this->bgColor());
    SetConsoleTextAttribute(WindowsHandler, colorId);
}

/**
 * @brief Print a std::string to screen and add a newline character at the end
 *
 * @param prompt
 * @param color
 */
void MenuManager::print(std::string prompt, int color) {
    color = (color == -1) ? this->defaultTextColor() : color;
    this->setColor(color);
    std::cout << prompt << std::endl;
    this->setColor(this->defaultTextColor());
}

/**
 * @brief Page loading pipeline (Do not overload)
 *
 * @param page
 */
void MenuManager::loadPage(Page page) {
    this->preloadPage(page);
    this->render(page);
    this->postLoadPage(page);
}

void MenuManager::preloadPage(Page page) {
    clearScreen();
}

/**
 * @brief Standard procedure to render a page, throw an exception if the number of displaying items is not equal to the number of selectables
 *
 * @param page
 */
void MenuManager::render(Page page) {
    std::vector<Selectable> selectables = page.getSelectables();
    if (this->direct()) {
        this->forceSetSelection(page.initialSelection());
        this->setDirect(false);
    }
    this->print(page.title(), this->_style.get<int>("titleColor"));
    this->print("");
    for (int i = 0; i < selectables.size(); i++) {
        if (this->currentSelection() == i) this->print(selectables[i].label(), this->_style.get<int>("selectingColor"));
        else this->print(selectables[i].label(), this->defaultTextColor());
    }
}

/**
 * @brief Handle event listening constructor
 *
 * @param page
 */
void MenuManager::postLoadPage(Page page) {
    this->eventListener(page);
}

/**
 * @brief Handle user inputs in the interface.
 * @todo: SEPERATING EVENT HANDLING INTO METHODS
 *
 * @param page
 */
void MenuManager::eventListener(Page page) {
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
                    }
                    catch (const std::invalid_argument& e) {
                        std::cout << e.what() << std::endl;
                        break;
                    }
                    if (dest.getAction().getModule() != nullptr) {
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
                    }
                    catch (const std::invalid_argument& e) {
                        std::cout << e.what() << std::endl;
                        break;
                    }
                    if (dest.getAction().getModule() != nullptr) {
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
            if (dest.getAction().getModule() == nullptr) continue;
            if (dest.getAction().isQuit()) {
                quitFlag = true;
                (dest.getAction().getModule())(this, page);
                break;
            }

            try {
                (dest.getAction().getModule())(this, page);
            }
            catch (const std::exception& e) {
                this->print(e.what(), Color::RED);
                continue;
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
void MenuManager::setDefaultTextColor(int color) {
    this->_defaultTextColor = color;
}

/**
 * @brief Safely set current user's selection, throw an exception if the selection cannot be found
 *
 * @param page
 * @param id
 */
void MenuManager::setSelection(Page page, int id) {
    if (id >= page.getSelectables().size()) {
        std::string msg = concatenateString({ "Exception at trying to select navigator ", std::to_string(id), " in page navigator size: ", 
                                            std::to_string(page.getSelectables().size()), "\n" });
        this->print(msg, Color::RED);
        return;
    }
    this->_currentSelection = id;
}

/**
 * @brief Explicitly set the menu current selection. This should only be used when the selection is knowingly available.
 *
 * @param id
 */
void MenuManager::forceSetSelection(int id) {
    this->_currentSelection = id;
}

/**
 * @brief Default quitting action
 */
void MenuManager::initQuit(MenuManager* m, Page& page) {
    std::string msg = (*m)._lang.get<std::string>("quitMessage");
    m->print(msg, Color::GRAY);
}

/**
 * @brief This function is a placeholder for selectable that doesn't have any action
 */
void MenuManager::doNothing(MenuManager* m, Page& page) {
}

std::string MenuManager::getMenuName() {
    return _menuName;
}

/**
 * @brief Provide an interface to cast from base MenuManager to child class
 * @note Returning type must be a pointer covariant with MenuManager
 *
 * @return MenuManager*
 */
MenuManager* MenuManager::linker(MenuManager* m) {
    return m;
}