#ifndef PING
# define PING

# include "base.h"

typedef struct	ping
{
	t_base	base;
	int		time_interval;
} t_ping;

t_ping	*init_ping(char *name, char *protocol, char *addr,
		char *time_interval);

void	ping_show(void *self, void *info);
void	ping_write(void	*self, void *info);
void	ping_destroy(void *self);

void 	*ping_monitor(void *self);

#endif
