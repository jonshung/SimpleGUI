#pragma once
#define _MENU_MANAGER_BASE_

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>

#include "WindowsIO.h"
#include "UnixIO.h"

#include "Config.h"
#include "utils/GeneralUtils.h"
#include "Page.h"
#include "Selectable.h"
#include "WindowsIO.h"

class Selectable;
class MenuManager;
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
    bool _updateFlag;
    bool _quitFlag;
    std::shared_ptr<Page> _currentPage;

public:
    ConfigManager _lang;
    ConfigManager _style;
    
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
    virtual MenuManager* linker(MenuManager*);
    IOInterface* IOHandler();

    MenuManager();
    ~MenuManager();

    virtual void eventListener();
    virtual void onArrow(int);
    virtual void onEnter();
    virtual void onKey();

    virtual void loadPage() final;
    virtual void preloadPage();
    virtual void render();
    virtual void postLoadPage();
    void setColor(int);

    static void initQuit(MenuManager*);
    static void doNothing(MenuManager*);
};