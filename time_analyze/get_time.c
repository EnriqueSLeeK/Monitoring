#include "monitor.h"

void	analyze_parse(t_time *time, int (*func)(void));
int		get_mode(char *protocol);

int		get_mode(char *protocol)
{
	if (strcmp("HTTP", protocol) == 0)
		return (1);
	if (strcmp("DNS", protocol) == 0)
		return (2);
	if (strcmp("PING", protocol) == 0)
		return (3);
	return (-1);
}

int		phttp_time(void)
{
	char	*token = strtok(NULL, " ");
	strtok(NULL, " ");
	token = strtok(NULL, " ");
	strtok(token, "=");
	return atof(strtok(NULL, "="));
}

int		pdns_time(void)
{
	char	*token = NULL;
	strtok(NULL, " ");
	token = strtok(NULL, " ");
	strtok(token, "=");
	return atof(strtok(NULL, "="));
}

int		pping_time(void)
{
	char	*token = NULL;
	strtok(NULL, " ");
	strtok(NULL, " ");
	strtok(NULL, " ");
	strtok(NULL, " ");
	token = strtok(NULL, " ");
	strtok(token, "=");
	return atof(strtok(NULL, "="));
}

void	analyze_parse(t_time *time, int (*get_time)(void))
{
	if (strcmp(strtok(NULL, " "), "Error")) // Error check
	{
		if (time -> quant == time -> size) // Get more memory
		{
			if ((time -> time = realloc(time -> time, time -> size * 2)) == NULL)
				return ;
			time -> size *= 2;
		}
		time -> time[time -> quant] = get_time();
		time -> quant += 1;
	}
}

void	parse(t_time *http_time, t_time *dns_time, t_time *ping_time)
{
	FILE	*file = fopen("monitoring.log", "r+");
	char	*tmp = NULL;
	char	*token = NULL;
	size_t	size_buff;

	if (file == NULL)
	{
		fprintf(stderr, "fopen() failure\n");
		return;
	}

	while (getline(&tmp, &size_buff, file) != -1)
	{
		nl_to_null(tmp);
		strtok(tmp, " ");
		strtok(NULL, " ");
		token = strtok(NULL, " ");
		switch	(get_mode(token)){
			case 1:
				analyze_parse(http_time, phttp_time);
				break;
			case 2:
				analyze_parse(dns_time, pdns_time);
				break;
			case 3:
				analyze_parse(ping_time, pping_time);
				break;
			default: break;
		}
		free(tmp);
		tmp = NULL;
	}
	free(tmp);
}
