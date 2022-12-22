#include "monitor.h"

static void	logger_callback(void *self, int status,
		int timeouts, struct hostent *host)
{
	t_dns	*dns = self;
	t_base	*base = self;

	if (status == ARES_SUCCESS)
	{
		t_aux	info;
		info.host = host;
		struct timeval	now;

		gettimeofday(&now, NULL);
		info.delta = (now.tv_sec - dns -> time.tv_sec) * 1000 +
			(now.tv_usec - dns -> time.tv_usec) / 1000;
		base -> show(self, (void *)&info);
		base -> write(self, (void *)&info);
	}
	else
	{
		base -> show(self, NULL);
		base -> write(self, NULL);
	}
}

void	*dns_monitor(void *self)
{
	ares_channel	ares;
	t_dns			*dns = self;
	t_base			*base = self;

	if (ares_init_options(&ares, &(dns -> flag),
				ARES_OPT_SERVERS) != ARES_SUCCESS)
		return (0);

	while (1)
	{
		gettimeofday(&(dns -> time), NULL);
		ares_gethostbyname(ares, base -> addr, AF_INET,
				logger_callback, self);

		int nfds, count;
		fd_set readers, writers;
		struct timeval tv, *tvp;
	 
		while (1)
		{
			FD_ZERO(&readers);
			FD_ZERO(&writers);
			nfds = ares_fds(ares, &readers, &writers);
			if (nfds == 0)
				break;
			tvp = ares_timeout(ares, NULL, &tv);
			count = select(nfds, &readers, &writers, NULL, tvp);
			ares_process(ares, &readers, &writers);
		}
		sleep(dns -> time_interval);
	}

	ares_destroy(ares);
	return (0);
}

