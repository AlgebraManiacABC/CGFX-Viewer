#ifndef EVENTS_H
#define EVENTS_H
#include "debug.h"

typedef struct EventPacket_s
{
	int eventCount;
	bool shouldClose;

}	* EventPacket;

EventPacket handleEvents();

#endif