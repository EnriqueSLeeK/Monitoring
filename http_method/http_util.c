#include "monitor.h"

void	http_destroy(void *self)
{
	t_http	*http = self;
	free(http -> method);
	destroy_base((t_base *)self);
	free(self);
}

// Do it later
void	http_show(void *self, void *curl_ptr)
{
	curl_off_t	res_time;
	curl_off_t	ret_code;
	t_http 		*http = self;
	t_base 		*base = self;
	CURL		*curl = curl_ptr;

	if (curl == NULL)
	{
		pthread_mutex_lock(&print_mutex);
		fprintf(stderr, "%s | %s Error\n",
				base -> name,
				base -> protocol);
		pthread_mutex_unlock(&print_mutex);
		return;
	}
	curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &res_time);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &ret_code);
	// HTTP monitor message
	// Nickname | protocol target_addr response_time \
	// return_code expectation_match
	pthread_mutex_lock(&print_mutex);
	fprintf(stdout, "%s | %s %d %s %s res=%ld ms %ld\n",
			base -> name,
			base -> protocol,
			ret_code == (long)http -> ret_code,
			http -> method,
			base -> addr,
			res_time / 1000,
			ret_code);
	pthread_mutex_unlock(&print_mutex);
}

void	http_write(void *self, void *curl_ptr)
{
	FILE		*file_fd;
	curl_off_t	res_time;
	curl_off_t	ret_code;
	t_http		*http = self;
	t_base		*base = self;
	CURL		*curl = curl_ptr;

	pthread_mutex_lock(&write_mutex);
	file_fd = fopen("monitoring.log", "a+");
	if (file_fd == 0)
	{
		fprintf(stderr, "fopen() failure!\n");
		return ;
	}

	if (curl == NULL)
	{
		fprintf(file_fd, "%s | %s Error\n",
				base -> name,
				base -> protocol);
		pthread_mutex_unlock(&write_mutex);
		fclose(file_fd);
		return ;
	}

	curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &res_time);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &ret_code);
	// HTTP monitor log format
	// Nickname | protocol target_addr response_time \
	// return_code expectation_match
	fprintf(file_fd, "%s | %s %d %s %s res=%ld ms %ld\n",
			base -> name,
			base -> protocol,
			ret_code == (long)http -> ret_code,
			http -> method,
			base -> addr,
			res_time / 1000,
			ret_code);
	fclose(file_fd);
	pthread_mutex_unlock(&write_mutex);
}
