#include "monitor.h"

void	dns_destroy(void *self)
{
	t_dns	*dns = self;

	destroy_base((t_base *)self);
	free(dns -> dns_server);
	free(dns);
}

void	dns_show(void *self, void *info)
{
	t_dns			*dns = self;
	t_base			*base = self;

	if (info == NULL)
	{
		pthread_mutex_lock(&print_mutex);
		fprintf(stdout, "%s | %s Error\n",
				base -> name,
				base -> protocol);
		pthread_mutex_unlock(&print_mutex);
		return ;
	}

	t_aux			*aux = info;
	struct hostent	*host = aux -> host;

	/*
	 * Name | protocol address lookup time(ms)
	 */
	pthread_mutex_lock(&print_mutex);
	fprintf(stdout, "%s | %s %s (%u.%u.%u.%u) lookup=%lld ms\n",
			base -> name,
			base -> protocol,
			base -> addr,
			(unsigned char)host -> h_addr[0], (unsigned char)host -> h_addr[1],
			(unsigned char)host -> h_addr[2], (unsigned char)host -> h_addr[3],
			aux -> delta);
	pthread_mutex_unlock(&print_mutex);
}

void	dns_write(void *self, void *info)
{
	t_dns			*dns = self;
	t_base			*base = self;

	pthread_mutex_lock(&write_mutex);
	FILE		*file_fd = fopen("monitoring.log", "a+");
	if (file_fd == 0)
		return ;

	if (info == NULL)
	{
		fprintf(file_fd, "%s | %s Error\n",
				base -> name,
				base -> protocol);
		pthread_mutex_unlock(&write_mutex);
		fclose(file_fd);
		return ;
	}

	t_aux			*aux = info;
	struct hostent	*host = aux -> host;

	/*
	 * Name | protocol address lookup time(ms)
	 */
	fprintf(file_fd, "%s | %s %s (%u.%u.%u.%u) lookup=%lld ms\n",
			base -> name,
			base -> protocol,
			base -> addr,
			(unsigned char)host -> h_addr[0], (unsigned char)host -> h_addr[1],
			(unsigned char)host -> h_addr[2], (unsigned char)host -> h_addr[3],
			aux -> delta);
	fclose(file_fd);
	pthread_mutex_unlock(&write_mutex);
}
