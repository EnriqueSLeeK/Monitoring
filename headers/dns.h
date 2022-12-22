#ifndef DNS
# define DNS

#include <ares.h>

typedef struct	dns
{
	t_base				base;
	int					time_interval;
	struct in_addr		*dns_server;
	struct ares_options	flag;
	struct timeval		time;
} t_dns;

typedef struct	aux {
	void				*host;
	long long int		delta;
} t_aux;

t_dns	*init_dns(char *name, char *protocol,
		char *addr, char *time_interval, char *dns_server);

void	dns_show(void *self, void *info);
void	dns_write(void *self, void *info);
void	dns_destroy(void *self);

void	*dns_monitor(void *self);

#endif
