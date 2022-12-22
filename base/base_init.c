#include "monitor.h"

void	init_base(t_base *self, char *name,
		char *protocol, char *addr,
		void (*show)(void *self, void *info),
		void (*write)(void *self, void *info),
		void (*destroy)(void *self),
		void *(*monitor)(void *self))
{
	self -> name = strdup(name);
	self -> protocol = strdup(protocol);
	self -> addr = strdup(addr);
	self -> show = show;
	self -> write = write;
	self -> destroy = destroy;
	self -> monitor = monitor;
}
