#pragma once
#define _MENU_MANAGER_

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <conio.h>

#include "Utils.h"

using std::cout, std::endl;
using std::vector;
using std::string;

class Selectable;
class Menu;

typedef Selectable (*SelectableNavigator)(Menu*);
typedef void (Selectable::*SelectableAction)();

class Menu {
private:
    int _bgColor;
    int _defaultTextColor;
    HANDLE _WindowsHandle = nullptr;
    int _currentSelection;
public:
    int bgColor() { return _bgColor; }
    int defaultTextColor() { return _defaultTextColor; }
    int currentSelection() { return _currentSelection; }
    void setDefaultTextColor(int color);
    void setSelection(Selectable page, int id);

    Menu();

    void eventListener(Selectable page);
    void print(string prompt, int color = Color::WHITE);
    void loadPage(Selectable page);
    void setColor(int colorId);
    static Selectable initQuit(Menu* m);
    static Selectable doNothing(Menu *m);
};

class Selectable {
private:
    Menu* _menuManager;
    std::string _title = "";
    bool _isPage = false;
    std::vector<string> _items;
    std::vector<SelectableNavigator> _navs;

public:
    string title() { return _title; }
    bool isPage() { return _isPage; }
    void setPage() { _isPage = true; }
    int itemCount() { return _items.size(); }
    vector<string> getItems() { return _items; }
    vector<SelectableNavigator> getNavigators() { return _navs; }
    Menu* menuManager() { return _menuManager; }
    
    SelectableNavigator getNavigator(int id);
    void addItem(string item);
    void removeItem(int id);

    Selectable(Menu* menuMgr, string title) {
        _menuManager = menuMgr;
        _title = title;
    }
    Selectable(Menu* menuMgr, string title, vector<string> items, vector<SelectableNavigator> navs) {
        _title = title;
        _items = items;
        _navs = navs;
    }

    Selectable(string title) {
        _menuManager = nullptr;
        _title = title;
    }
    Selectable( string title, vector<string> items, vector<SelectableNavigator> navs) {
        _menuManager = nullptr;
        _title = title;
        _items = items;
        _navs = navs;
    }
};