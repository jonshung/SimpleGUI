#include "KeyboardEventListener.h"

/**
 * @brief Handle user inputs in the interface.
 * Overridable
 *
 * @param page
 */
void KeyboardEventListener::listen(MenuManager* menuHandler) {
	while (!menuHandler->isQuit()) {
		unsigned char key = menuHandler->IOHandler()->getChar();
		if (isArrowKey(key)) {
			this->onArrowKey(menuHandler, key);
		}
		else if (Keys::ENTER == key) {
			this->onEnterKey(menuHandler, key);
		}
		else {
			this->onAlphaNumericKey(menuHandler, key);
		}
		if (menuHandler->direct()) {
			break;
		}
		menuHandler->render();
	}
	if (menuHandler->direct()) menuHandler->loadPage();
}

/**
 * @brief Experimental feature
*/
void KeyboardEventListener::onAlphaNumericKey(MenuManager* menuHandler, unsigned char key) {
	// todo
}

/**
 * @brief Handle user enter key
*/
void KeyboardEventListener::onEnterKey(MenuManager* menuHandler, unsigned char key) {
	Page& page = *(menuHandler->getCurrentPage());

	Selectable dest = page.getSelectable(menuHandler->currentSelection());
	SelectableAction& action = *(dest.getAction());
	if (action.getModule() == nullptr) return;
	if (action.isQuit()) {
		menuHandler->quit();
		(action.getModule())(menuHandler);
	}
	else {
		try {
			(action.getModule())(menuHandler);
		}
		catch (const std::exception& e) {
			menuHandler->IOHandler()->print(e.what(), { "9" });
			menuHandler->quit();
		}
	}
}

/**
 * @brief On arrow action, typically changing the selection of the user.
 * Overridable
 *
 * @param c
*/
void KeyboardEventListener::onArrowKey(MenuManager* menuHandler, unsigned char key) {
	Page& page = *(menuHandler->getCurrentPage());
	int selection = menuHandler->currentSelection();
	switch (key) {
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
				menuHandler->setSelection(page, selection);
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
				menuHandler->setSelection(page, selection);
				break;
			}
		}
		break;
	}
	default: break;
	}
}