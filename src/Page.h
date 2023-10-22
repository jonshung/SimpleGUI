#pragma once
#define _PAGE_BASE_

#include <string>
#include <vector>
#include "Selectable.h"

class Page;
class MenuManager;
class SelectableAction;
class Selectable;
typedef void (*ActionType)(MenuManager*);

class Page {
private:
    std::string _title = "";
    std::vector<Selectable> _selectables;
    int _initialSelection;

public:
    std::string title();
    int initialSelection();
    void setInitialSelection(int);
    std::vector<Selectable>& getSelectables();

    Selectable getSelectable(int);
    void addSelectable(Selectable);
    void removeItem(int);
    static void setSelectablesActions(std::vector<Selectable>&, ActionType);

    void reset(std::string title = "", std::vector<Selectable> = std::vector<Selectable>());

    Page();
    Page(std::string);
    Page(std::string, std::vector<Selectable>);
};