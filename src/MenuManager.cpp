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

void MenuManager::setDirectTarget(std::shared_ptr<Page> page) {
    this->_currentPage.reset();
    this->_currentPage = page;
    this->setDirect(true);
}

/**
 * @brief Construct a new MenuManager:: MenuManager object
 *
 */
MenuManager::MenuManager() {
    _direct = false;
    #if _WIN32
    _IOHandler = WindowsIO::instance();
    #endif
    #if __unix
    _IOHandler = UnixIO::instance();
    #endif
    _currentSelection = 0;
    this->_lang = ConfigManager("config/us.json");
    this->_style = ConfigManager("config/style.json");

    _bgColor = _style.get<int>("defaultBackgroundColor");
    _bgColor = (_bgColor == -1) ? Color::BLACK : _bgColor;
    _defaultTextColor = _style.get<int>("defaultTextColor");
    _defaultTextColor = (_defaultTextColor == -1) ? Color::WHITE : _defaultTextColor;
}

IOInterface* MenuManager::IOHandler() {
    return _IOHandler;
}

MenuManager::~MenuManager() {
    delete _IOHandler;
}

/**
 * @brief Page loading pipeline (Do not overload)
 *
 * @param page
 */
void MenuManager::loadPage() {
    _updateFlag = false;
    this->preloadPage();
    this->render();
    this->postLoadPage();
}

void MenuManager::preloadPage() {
    if (!_debug) IOHandler()->clearScreen();
}

/**
 * @brief Standard procedure to render a page, throw an exception if the number of displaying items is not equal to the number of selectables
 *
 * @param page
 */
void MenuManager::render() {
    Page& page = *(_currentPage);
    std::vector<Selectable> selectables = page.getSelectables();
    if (this->direct()) {
        this->forceSetSelection(page.initialSelection());
        this->setDirect(false);
    }
    IOHandler()->print(page.title() + "\n", { this->_style.get<std::string>("titleColor") });
    for (int i = 0; i < selectables.size(); i++) {
        if (this->currentSelection() == i) IOHandler()->print(selectables[i].label(), { this->_style.get<std::string>("selectingColor") });
        else IOHandler()->print(selectables[i].label(), { /* standard color */ });
    }
}

/**
 * @brief Handle event listening constructor
 *
 * @param page
 */
void MenuManager::postLoadPage() {
    this->eventListener();
}

/**
 * @brief Handle user inputs in the interface.
 *
 * @param page
 */
void MenuManager::eventListener() {
    Page& page = *(_currentPage);
    while (!_updateFlag) {
        unsigned char key = IOHandler()->getChar();
        if (isArrowKey(key)) {
            this->onArrow(key);
        }
        if (Keys::ENTER == key) {
            this->onEnter();
        }
    }
    if (!_quitFlag) loadPage();
}

void MenuManager::onArrow(int c) {
    Page& page = *(_currentPage);
    int selection = this->currentSelection();
    switch (c) {
    case Keys::UP: {
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
            if (dest.getAction() != nullptr) {
                this->setSelection(page, selection);
                _updateFlag = true;
                break;
            }
        }
        break;
    }
    case Keys::DOWN: {
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
            if (dest.getAction() != nullptr) {
                this->setSelection(page, selection);
                _updateFlag = true;
                break;
            }
        }
        break;
    }
    default: break;
    }
}

void MenuManager::onKey() {
    //todo
}

void MenuManager::onEnter() {
    Page& page = *(_currentPage);

    Selectable dest = page.getSelectable(this->currentSelection());
    SelectableAction& action = *(dest.getAction());
    if (action.getModule() == nullptr) return;
    if (action.isQuit()) {
        _quitFlag = true;
        (action.getModule())(this);
    }
    else {
        try {
            (action.getModule())(this);
        }
        catch (const std::exception& e) {
            IOHandler()->print(e.what(), { "9" });
            _quitFlag = true;
        }
    }
    _updateFlag = true;
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
        IOHandler()->print(msg, { "9" });
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
void MenuManager::initQuit(MenuManager* m) {
    std::string msg = (*m)._lang.get<std::string>("quitMessage");
    m->IOHandler()->print(msg, { "8" });
}

/**
 * @brief This function is a placeholder for selectable that doesn't have any action
 */
void MenuManager::doNothing(MenuManager* m) {
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