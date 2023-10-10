#pragma once
#define _MENU_MANAGER_

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <conio.h>
#include <stdexcept>

#include "Utils.h"

using std::cout, std::endl;
using std::vector;
using std::string;

class Selectable;
class Page;
class Menu;

/**
 * @params
 * Menu*    MenuHandler pointing to current opening menu.
 * Page&    Current page, to direct/redirect to other page, set this parameter to the destination page.
 */
typedef void (*SelectableAction)(Menu*, Page&);

class Menu {
private:
    int _bgColor;
    int _defaultTextColor;
    HANDLE _WindowsHandle = nullptr;
    int _currentSelection;
    bool _direct;
public:
    int bgColor() { return _bgColor; }
    int defaultTextColor() { return _defaultTextColor; }
    int currentSelection() { return _currentSelection; }
    void setDefaultTextColor(int color);
    void setSelection(Page page, int id);
    void forceSetSelection(int id);
    bool direct() { return _direct; }
    void setDirect(bool vl) { _direct = vl; }

    Menu();

    void eventListener(Page page);
    void print(string prompt, int color = Color::WHITE);
    void loadPage(Page page);
    void setColor(int colorId);
    static void initQuit(Menu* m, Page &page);
    static void doNothing(Menu* m, Page &page);
};

class Page {
private:
    std::string _title = "";
    std::vector<Selectable> _selectables;
    Page();

public:
    string title() { return _title; }
    vector<Selectable> getSelectables() { return _selectables; }

    Selectable getSelectable(int id);
    void addSelectable(Selectable Selectable);
    void removeItem(int id);
    void allDoNothing();

    static void doNothingVector(vector<Selectable>& list);

    Page(string title) {
        _title = title;
    }
    Page(string title, vector<Selectable> selectables) {
        _title = title;
        _selectables = selectables;
    }
};

class Selectable {
private:
    string _label;
    SelectableAction _action;
public:
    string label() { return _label; }
    SelectableAction getAction() { return _action; }
    void setAction(SelectableAction action) { _action = action; }
    Selectable(string label, SelectableAction action) {
        _label = label;
        _action = action;
    }
    Selectable(string label) {
        _label = label;
        _action = nullptr;
    }
    Selectable() {
        _label = "";
        _action = nullptr;
    }
};