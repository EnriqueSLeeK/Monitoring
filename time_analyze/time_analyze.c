#include "monitor.h"

double	get_median(t_time *time, int offset);
double	get_sort_mean(t_time *time);
int		count_outlier(t_time *time, double median);
void	parse(t_time *http_time, t_time *ping_time, t_time *dns_time);

static void		print_result(double http_median, double http_mean, int http_outlier,
								double dns_median, double dns_mean, int dns_outlier,
								double ping_median, double ping_mean, int ping_outlier);


static int		do_operation(t_time *http, t_time *dns, t_time *ping,
							 double *mean, double *median, int *outlier)
{
	mean[0] = get_sort_mean(http);
	mean[1] = get_sort_mean(dns);
	mean[2] = get_sort_mean(ping);

	median[0] = get_median(http, 0);
	median[1] = get_median(dns, 0);
	median[2] = get_median(ping, 0);

	if (http -> quant > 5)
		outlier[0] = count_outlier(http, median[0]);
	if (dns -> quant > 5)
		outlier[1] = count_outlier(dns, median[1]);
	if (ping -> quant > 5)
		outlier[2] = count_outlier(ping, median[2]);
	return (0);
}

static void	init_time(t_time *time, int size)
{
	time -> quant = 0;
	time -> size = size;
	time -> time = calloc(sizeof(double), size);
}

void	time_analyze(void)
{
	FILE	*fd_file = fopen("monitoring.log", "r+");

	int	size = 100;
	// First element is the quantity
	
	t_time	http;
	t_time	dns;
	t_time	ping;
	
	init_time(&http, size);
	init_time(&dns, size);
	init_time(&ping, size);

	parse(&http, &ping, &dns);

	/* index
	 * 0 - http
	 * 1 - dns
	 * 2 - ping
	 */
	double	mean[3] = {0, 0, 0};
	double	median[3] = {0, 0, 0};
	int		upper_outlier[3] = {0, 0, 0};

	do_operation(&http, &dns, &ping,
			mean, median, upper_outlier);

	free(http.time);
	free(dns.time);
	free(ping.time);

	print_result(mean[0], median[0], upper_outlier[0],
			mean[1], median[1], upper_outlier[1],
			mean[2], median[2], upper_outlier[2]);
}

static void	print_result(double http_median, double http_mean, int http_outlier,
		double dns_median, double dns_mean, int dns_outlier,
		double ping_median, double ping_mean, int ping_outlier)
{
	fprintf(stdout, "Protocol |       Mean     Median     Quant_Outlier\n");

	fprintf(stdout, "HTTP     | % 10.3lf % 10.3lf % 10d\n", http_median, http_mean, http_outlier);
	fprintf(stdout, "DNS      | % 10.3lf % 10.3lf % 10d\n", dns_median, dns_mean, dns_outlier);
	fprintf(stdout, "PING     | % 10.3lf % 10.3lf % 10d\n", ping_median, ping_mean, ping_outlier);
}
