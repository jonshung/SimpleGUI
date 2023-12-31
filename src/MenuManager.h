#pragma once
#define _MENU_MANAGER_BASE_

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <filesystem>

#include "WindowsIO.h"
#include "UnixIO.h"

#include "LocalizeConfig.h"
#include "utils/GeneralUtils.h"
#include "Page.h"
#include "Selectable.h"
#include "WindowsIO.h"
#include "KeyboardEventListener.h"
#include "StylePopulator.h"

class KeyboardEventListener;
class Selectable;
class Page;

typedef void (*ActionType)(MenuManager*);

class MenuManager {
private:
    bool _debug = false;
    std::string _menuName;
    int _bgColor;
    int _defaultTextColor;
    IOInterface* _IOHandler;
    int _currentSelection;
    
    bool _direct;
    bool _quitFlag;
    std::shared_ptr<Page> _currentPage;

    std::shared_ptr<KeyboardEventListener> _keyboardListener;
public:
    inline static LocalizeConfig _lang;
    inline static ConfigManager _style;
    virtual std::string getMenuName();
    int bgColor();
    int defaultTextColor();
    int currentSelection();
    void setDefaultTextColor(int);
    void setSelection(Page, int);
    void forceSetSelection(int);
    bool direct();
    void setDirect(bool);
    void setDirectTarget(std::shared_ptr<Page>);
    static MenuManager* linker(MenuManager*);
    IOInterface* IOHandler();
    LocalizeConfig getLang();
    ConfigManager getStyle();
    std::shared_ptr<Page> getCurrentPage();

    MenuManager();
    ~MenuManager();

    virtual void loadPage() final;
    virtual void preloadPage();
    virtual void render();
    virtual void postLoadPage();
    bool isQuit();
    void quit();

    static void initQuit(MenuManager*);
    static void doNothing(MenuManager*);
};