#include "monitor.h"

t_ping	*init_ping(char *name, char *protocol, char *addr,
		char *time_interval)
{
	t_ping	*ping = malloc(sizeof(t_ping));
	init_base((t_base *)ping, name, protocol, addr,
			ping_show, ping_write, ping_destroy, ping_monitor);
	ping -> time_interval = atoi(time_interval);
	return (ping);
}
