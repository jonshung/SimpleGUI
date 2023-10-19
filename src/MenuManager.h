#pragma once
#define _MENU_MANAGER_BASE_

#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <stdexcept>

#include "Config.h"
#include "utils/GeneralUtils.h"
#include "Page.h"
#include "Selectable.h"
#include "WindowsOutput.h"

class Selectable;
class Page;

class MenuManager {
private:
    bool _debug = false;
    std::string _menuName;
    int _bgColor;
    int _defaultTextColor;
    WindowsOutput* _OutputHandler;
    int _currentSelection;
    bool _direct;
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
    virtual MenuManager* linker(MenuManager*);
    WindowsOutput outputHandler();

    MenuManager();

    void eventListener(Page);
    virtual void loadPage(Page) final;
    virtual void preloadPage(Page);
    virtual void render(Page page);
    virtual void postLoadPage(Page);
    void setColor(int);
    static void initQuit(MenuManager*, Page&);
    static void doNothing(MenuManager*, Page&);
};