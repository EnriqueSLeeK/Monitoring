#include "monitor.h"

void	print_result(int http_count, int http_error, int match,
		int dns_count, int dns_error,
		int ping_count, int ping_error);

int		get_index(char *protocol)
{
	if (strcmp(protocol, "HTTP") == 0)
		return (0);
	if (strcmp(protocol, "DNS") == 0)
		return (1);
	if (strcmp(protocol, "PING") == 0)
		return (2);
	return (0);
}

void	count_protocols(void)
{
	FILE	*file = fopen("monitoring.log", "r+");
	char	*tmp = NULL;
	size_t	buff_size;

	/*
	 * index meaning
	 * 0 - http
	 * 1 - dns
	 * 2 - ping
	 */
	int		match = 0;
	int		index = 0;
	int		count[3] = {0,0,0};
	int		error_count[3] = {0,0,0};
	char	*token;

	if (file == NULL)
	{
		fprintf(stderr, "Error at fopen()\n");
		return ;
	}

	while (getline(&tmp, &buff_size, file) != -1)
	{
		nl_to_null(tmp);
		strtok(tmp, " "); // Consume name
		strtok(NULL, " "); // Consume |
		token = strtok(NULL, " "); // Protocol
		index = get_index(token);
		count[index] += 1;

		token = strtok(NULL, " "); // Error or match for http
		if (strcmp(token, "Error") == 0) // Error or not
			error_count[index] += 1;
		else if (index == 0 && strcmp(token, "1") == 0)
			match += 1;
	}
	fclose(file);
	free(tmp);
	print_result(count[0], error_count[0], match,
			count[1], error_count[1],
			count[2], error_count[2]);
}

void	print_result(int http_count, int http_error, int match,
		int dns_count, int dns_error, int ping_count, int ping_error)
{
	fprintf(stdout, "Protocols | Count     Error Expectation match <Only http>\n");

	fprintf(stdout, "HTTP      | % 5d	error=%d		Good=%d Not_match=%d\n",
			http_count, http_error, match, (http_count - http_error) - match);

	fprintf(stdout, "DNS       | % 5d	error=%d\n", dns_count, dns_error);

	fprintf(stdout, "PING      | % 5d	error=%d\n", ping_count, ping_error);
}
