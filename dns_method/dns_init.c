#include "monitor.h"

static int		get_ip(char *ip);
static int		count_how_many_server(char *dns_server);
static void		fill_ip_list(char *servers, char **ip_list, int quant);

t_dns	*init_dns(char *name, char *protocol,
		char *addr, char *time_interval, char *dns_server)
{
	t_dns	*dns = malloc(sizeof(t_dns));
	int		server_quant = count_how_many_server(dns_server);
	char	**ip_addrs = calloc(sizeof(char *), server_quant);

	init_base((t_base *)dns, name, protocol, addr,
			dns_show, dns_write, dns_destroy, dns_monitor);

	fill_ip_list(dns_server, ip_addrs, server_quant);
	dns -> dns_server = calloc(sizeof(struct in_addr),
								server_quant);

	for (int i = 0; i < server_quant; i++)
		dns -> dns_server[i].s_addr = get_ip(ip_addrs[i]);

	dns -> flag.servers = dns -> dns_server;
	dns -> flag.nservers = server_quant;

	dns -> time_interval = atoi(time_interval);

	free(ip_addrs);
	return (dns);
}

static int		count_how_many_server(char *dns_server)
{
	char	*tmp = strdup(dns_server);
	char	*token = strtok(tmp, ",");
	int		count = 0;

	do {
		count += 1;
		token = strtok(NULL, ",");
	} while (token);
	free(tmp);
	return (count);
}

static void		fill_ip_list(char *servers, char **ip_list,
								int quant)
{
	ip_list[0] = strtok(servers, ",");
	for (int i = 1; i < quant; i++)
		ip_list[i] = strtok(NULL, ",");
}

static int		get_ip(char *ip)
{
	int		addr = 0;
	char	*ip_segment = strtok(ip, ".");

	int		p = 0;
	while (ip_segment)
	{
		addr += atoi(ip_segment) << 8 * p; // parse integer
		ip_segment = strtok(NULL, ".");
		p += 1;
	}
	return (addr);
}
