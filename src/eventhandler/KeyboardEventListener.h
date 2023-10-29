#ifndef _KEYBOARD_EVENT_LISTENER_H_
#define _KEYBOARD_EVENT_LISTENER_H_

#include "EventListener.h"
#include "MenuManager.h"

class MenuManager;

class KeyboardEventListener : public EventListener {
public:
	void listen(MenuManager*);
	virtual void onAlphaNumericKey(MenuManager*, unsigned char);
	virtual void onArrowKey(MenuManager*, unsigned char);
	virtual void onEnterKey(MenuManager*, unsigned char);
};

#endif