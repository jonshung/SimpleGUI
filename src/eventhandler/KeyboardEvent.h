#ifndef _KEYBOARD_EVENT_H_
#define _KEYBOARD_EVENT_H_

// to be used

#include "Event.h"

class KeyboardEvent : public Event {
private:
	unsigned int _raw;
	unsigned int _translated;
public:
	KeyboardEvent();
	KeyboardEvent(unsigned int);

	bool translate();
};
#endif