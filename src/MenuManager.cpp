#include "MenuManager.h"

Menu::Menu() {
    _WindowsHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    _bgColor = Color::BLACK;
    _defaultTextColor = Color::WHITE;
    _currentSelection = 0;
}

void Menu::setColor(int colorId) {
    HANDLE WindowsHandler = this->_WindowsHandle;
    int colorOffset = getTextColor(colorId, this->bgColor());
    SetConsoleTextAttribute(WindowsHandler, colorId);
}

void Menu::print(string prompt, int color) {
    this->setColor(color);
    cout << prompt << endl;
    this->setColor(this->defaultTextColor());
}

void Menu::loadPage(Selectable page) {
    clearScreen();
    this->print(page.title(), Color::GREEN);
    this->print("");
    vector<string> items = page.getItems();
    for (int i = 0; i < items.size(); i++) {
        if (this->currentSelection() == i) this->print(items[i], Color::PALE_YELLOW);
        else this->print(items[i], this->defaultTextColor());
    }
    // TODO: FINISH
    this->eventListener(page);

}

/**
 * @brief HANDLING USER INPUT ON A PAGE
 * @todo: SEPERATING EVENT HANDLING INTO METHODS
 *
 * @param page
 */
void Menu::eventListener(Selectable page) {
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
                    SelectableNavigator dest = page.getNavigator(selection);
                    if (dest != nullptr) {
                        this->setSelection(page, selection);
                        updateFlag = true;
                        break;
                    }
                }
                break;
            }
            case Keys::Down: {
                while (selection < page.getNavigators().size() - 1) {
                    ++selection;
                    SelectableNavigator dest = page.getNavigator(selection);
                    if (dest != nullptr) {
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
            SelectableNavigator dest = page.getNavigator(this->currentSelection());
            if (dest == nullptr) continue;
            if (dest == (void*) &initQuit) {
                quitFlag = true;
                this->print("Quitting program...", Color::GRAY);
                break;
            }
            Selectable item = (dest)(this);
            if(item.isPage()) {
                this->setSelection(page, 0);
                page = item;
            }
            updateFlag = true;
        }
        if (updateFlag) break;
    }
    if (!quitFlag) loadPage(page);
}

void Menu::setDefaultTextColor(int color) {
    this->_defaultTextColor = color;
}

void Menu::setSelection(Selectable page, int id) {
    if (id >= page.getNavigators().size()) {
        string msg = concatenateString({ "Exception at trying to select navigator ", std::to_string(id), " in page navigator size: ", std::to_string(page.getNavigators().size()), "\n" });
        this->print(msg, Color::RED);
        return;
    }
    this->_currentSelection = id;
}

Selectable Menu::initQuit(Menu* m) {
    Selectable quitPage("");
    return quitPage;
}

Selectable Menu::doNothing(Menu* m) {
    Selectable doNothingPage("");
    return doNothingPage;
}

// Class page
void Selectable::addItem(string item) {
    _items.push_back(item);
}

void Selectable::removeItem(int id) {
    if (id >= this->getItems().size() || id < 0) {
        string msg = concatenateString({ "Exception at removing page item id: ", std::to_string(id), " at page size: ", std::to_string(_items.size()), "\n" });
        if (this->menuManager() == nullptr) {
            cout << "Invalid operation to orphan page\n";
            return;
        }
        (*this->menuManager()).print(msg, Color::RED);
        return;
    }
    _items.erase(_items.begin() + id);
}

SelectableNavigator Selectable::getNavigator(int id) {
    if (id >= this->getNavigators().size() || id < 0) {
        string msg = concatenateString({ "Exception at getting page navigator id: ", std::to_string(id), " from page size: ", std::to_string(_navs.size()), "\n" });
        if (this->menuManager() == nullptr) {
            cout << "Invalid operation to orphan page\n";
            return nullptr;
        }
        (*this->menuManager()).print(msg, Color::RED);
        return nullptr;
    }
    return _navs[id];
}