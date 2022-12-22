#include "monitor.h"

void	*init_and_parse(char *name, char *protocol)
{
	if (strcmp(protocol, "HTTP") == 0)
		return (init_http(name, protocol,
					strtok(NULL, "\t"), strtok(NULL, "\t"),
					strtok(NULL, "\t"), strtok(NULL, "\t")));
	if (strcmp(protocol, "PING") == 0)
		return (init_ping(name, protocol,
					strtok(NULL, "\t"), strtok(NULL, "\t")));
	if (strcmp(protocol, "DNS") == 0)
		return (init_dns(name, protocol,
					strtok(NULL, "\t"), strtok(NULL, "\t"),
					strtok(NULL, "\t")));
	return (0);
}
