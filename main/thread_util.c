#include "monitor.h"

int	start_monitoring(void **obj, pthread_t *threads)
{
	t_base		*base;

	for (int i = 0; obj[i]; i++)
	{
		base = obj[i];
		if (pthread_create(&(threads[i]), 0, base -> monitor, base))
		{
			thread_cancel(threads, i + 1);
			return (1);
		}
	}
	return (0);
}

void	wait_threads(pthread_t	*threads, int quant)
{
	for (int i = 0; i < quant; i++)
		pthread_join(threads[i], NULL);
}

void	thread_cancel(pthread_t *threads, int quant)
{
	for (int i = 0; i < quant; i++)
		pthread_cancel(threads[i]);
}
