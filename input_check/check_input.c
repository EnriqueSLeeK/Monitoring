#include "monitor.h"

static int	check_http(char *line);
static int	check_ping(char *line);
static int	check_dns(char *line);

int	check_line(char *line)
{
	char			*token = 0;
	char			*dup = strdup(line);

	token = strtok(dup, "\t"); // get_name
	
	// Check name
	if (!line || regex_match(token, "^[a-zA-Z0-9]+(_?+[a-zA-Z0-9]+)+$")) 
	{
		free(dup);
		return (1);
	}
	token = strtok(NULL, "\t"); // get protocol
	if (strcmp(token, "HTTP") == 0)
		return (check_http(dup));
	else if (strcmp(token, "PING") == 0)
		return (check_ping(dup));
	else if (strcmp(token, "DNS") == 0)
		return (check_dns(dup));
	write(2, "Unkown protocol\n", 16);
	free(dup);
	return (1);
}

static int check_http(char *line)
{
	/*
	 * Checking in order
	 * - address
	 * - http method
	 * - return code
	 * - time interval
	 */
	if (check_address(strtok(NULL, "	")) ||
		regex_match(strtok(NULL, "	"), "^[A-Z]+$") ||
		regex_match(strtok(NULL, "	"), "^[1-9][0-9]{2,2}$") ||
		regex_match(strtok(NULL, "	"), "^[1-9]([0-9]+)?$"))
	{
		free(line);
		return (1);
	}
	free(line);
	return (0);
}

static int check_ping(char *line)
{
	/*
	 * Checking in order
	 * - address
	 * - time interval
	 */
	if (check_address(strtok(NULL, "	")) ||
		regex_match(strtok(NULL, "	"), "^[1-9]([0-9]+)?$"))
	{
		free(line);
		return (1);
	}
	free(line);
	return (0);
}

static int check_dns(char *line)
{
	/*
	 * Checking in order
	 * - address
	 * - time interval
	 * - dns server <ip4>,<ip4>,<ip4>,....
	 */
	if (check_address(strtok(NULL, "	")) ||
		regex_match(strtok(NULL, "	"), "^[1-9]([0-9]+)?$") ||
		regex_match(strtok(NULL, "	"),
			"^(([0-9]{1,3}\\.){3,3}[0-9]{1,3})+((,([0-9]{1,3}\\.){3,3}[0-9]{1,3})+)?$"))
	{
		free(line);
		return (1);
	}
	free(line);
	return (0);
}
