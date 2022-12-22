#include "monitor.h"

void	ping_show(void *self, void *info)
{
	char	**inf = info;
	t_ping	*ping = self;
	t_base	*base = self;

	pthread_mutex_lock(&print_mutex);

	if (inf == NULL)
		fprintf(stderr, "%s | %s Error\n",
				base -> name,
				base -> protocol);

	else
		fprintf(stdout, "%s | %s %s %s %s bytes %s %s ms\n",
				base -> name,
				base -> protocol,
				base -> addr,
				inf[1],
				inf[0],
				inf[2],
				inf[4]);
	pthread_mutex_unlock(&print_mutex);
}

void	ping_write(void	*self, void *info)
{
	char	**inf = info;
	t_ping	*ping = self;
	t_base	*base = self;

	pthread_mutex_lock(&write_mutex);
	FILE		*file_fd = fopen("monitoring.log", "a+");
	if (file_fd == 0)
		return ;

	if (inf == NULL)
		fprintf(file_fd, "%s | %s Error\n",
				base -> name,
				base -> protocol);

	else
		fprintf(file_fd, "%s | %s %s %s %s bytes %s %s ms\n",
				base -> name,
				base -> protocol,
				base -> addr,
				inf[1],
				inf[0],
				inf[2],
				inf[4]);
	fclose(file_fd);
	pthread_mutex_unlock(&write_mutex);
}

void	ping_destroy(void *self)
{
	destroy_base((t_base *)self);
	free(self);
}
