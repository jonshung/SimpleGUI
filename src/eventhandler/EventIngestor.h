#ifndef _EVENT_INGESTOR_H
#define _EVENT_INGESTOR_H

#include "Event.h"
#include <memory>
class EventIngestor {
private:
	std::shared_ptr<Event> _eventQueue;
};
#endif