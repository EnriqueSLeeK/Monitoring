#include "monitor.h"

t_http	*init_http(char *name, char *protocol,
		char *addr, char *method,
		char *ret_code, char *time_interval)
{
	t_http	*http = malloc(sizeof(t_http));
	if (http == 0)
		return (0);

	init_base((t_base *)http, name, protocol, addr,
			http_show, http_write, http_destroy, http_monitor);

	http -> method = strdup(method);
	http -> ret_code = atoi(ret_code);
	http -> time_interval = atoi(time_interval);

	if (strcmp(http -> method, "GET") == 0)
		http -> request_method = get_method;
	else if (strcmp(http -> method, "POST") == 0)
		http -> request_method = post_method;
	else if (strcmp(http -> method, "PUT") == 0)
		http -> request_method = put_method;
	else if (strcmp(http -> method, "HEAD") == 0)
		http -> request_method = head_method;
	else
		http -> request_method = generic_method;

	return (http);
}
