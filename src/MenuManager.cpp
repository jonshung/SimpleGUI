#include "MenuManager.h"

/**
 * @brief Get default text color of the interface
 * @return 
*/
int MenuManager::defaultTextColor() {
    return _defaultTextColor;
}

/**
 * @brief Get application-wide background color
 * @return 
*/
int MenuManager::bgColor() {
    return _bgColor;
}

/**
 * @brief Return client's current selection in the current Page component
 * @return 
*/
int MenuManager::currentSelection() {
    return _currentSelection;
}

/**
 * @brief If next page render should be a redirection to another Page component
 * @return 
*/
bool MenuManager::direct() {
    return _direct;
}

/**
 * @brief Set Redirect flag
 * @param vl 
*/
void MenuManager::setDirect(bool vl) {
    _direct = vl;
}

/**
 * @brief Set the redirecting Page componenet, should be used with setDirect()
 * @param page 
*/
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
    _quitFlag = false;
    if(!std::filesystem::is_directory("./config")) {
        std::filesystem::create_directory(std::filesystem::path("./config"));
    }
    _style = ConfigManager("config/style.json", StylePopulator::getDefaultPopulator());

    _bgColor = _style.get<int>("defaultBackgroundColor");
    _bgColor = (_bgColor == -1) ? Color::BLACK : _bgColor;
    _defaultTextColor = _style.get<int>("defaultTextColor");
    _defaultTextColor = (_defaultTextColor == -1) ? Color::WHITE : _defaultTextColor;

    _keyboardListener = std::make_shared<KeyboardEventListener>();
}

/**
 * @brief Return the In/Out handler of this Menu instance
 * @return 
*/
IOInterface* MenuManager::IOHandler() {
    return _IOHandler;
}

LocalizeConfig MenuManager::getLang() {
    return _lang;
}

ConfigManager MenuManager::getStyle() {
    return _style;
}

MenuManager::~MenuManager() {
    delete _IOHandler;
}

/**
 * @brief Page loading pipeline (Do not overload)
 *
 * 
 * @param page
 */
void MenuManager::loadPage() {
    this->preloadPage();
    this->render();
    this->postLoadPage();
}


std::shared_ptr<Page> MenuManager::getCurrentPage() {
    return _currentPage;
}

/**
 * @brief General Preloading opertion on a page
 * Overridable
*/
void MenuManager::preloadPage() {
    Page& page = *(_currentPage);
    page.preload();
}

/**
 * @brief Standard procedure to render a page, throw an exception if the number of displaying items is not equal to the number of selectables
 * Overridable
 *
 * @param page
 */
void MenuManager::render() {
    if (!_debug) IOHandler()->clearScreen();
    Page& page = *(_currentPage);
    std::vector<Selectable> selectables = page.getSelectables();
    if (this->direct()) {
        this->forceSetSelection(page.initialSelection());
        this->setDirect(false);
    }
    IOHandler()->print(page.title() + "\n", { this->getStyle().get<std::string>("titleColor") });
    for (int i = 0; i < selectables.size(); i++) {
        if (this->currentSelection() == i) IOHandler()->print(selectables[i].label(), { this->getStyle().get<std::string>("selectingColor")});
        else IOHandler()->print(selectables[i].label(), { /* standard color */ });
    }
}

/**
 * @brief Initialize event listening, will be deprecated in the near future following the implementation of Multi threaded event handler
 * Overridable
 *
 * @param page
 */
void MenuManager::postLoadPage() {
    _keyboardListener->listen(this);
}

/**
 * @brief Set the quit flag for the program
*/
void MenuManager::quit() {
    _quitFlag = true;
}

bool MenuManager::isQuit() {
    return _quitFlag;
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
    m->IOHandler()->clearScreen();
    std::string msg = "Quiting program...";
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