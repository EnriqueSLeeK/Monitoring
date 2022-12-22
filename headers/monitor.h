#ifndef MONITOR
# define MONITOR

#include <curl/curl.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <regex.h>
#include <ctype.h>
#include <fcntl.h>
#include <ares.h>

#include "ping.h"
#include "base.h"
#include "http.h"
#include "dns.h"

typedef struct	timer
{
	int		size;
	int		quant;
	double	*time;
} t_time;

extern pthread_mutex_t	write_mutex;
extern pthread_mutex_t	print_mutex;

void	*init_and_parse(char *name, char *protocol);

void	count_protocols(void);
void	time_analyze(void);

// Checkers
int		check_line(char *line);
int		check_address(char *segment);
int		regex_match(char *segment, char *pattern);

// Destroy
void	destroy_obj(void **obj);

void	nl_to_null(char *);

// Threads util
int		start_monitoring(void **obj, pthread_t *threads);
void	wait_threads(pthread_t	*threads, int quant);
void	thread_cancel(pthread_t *threads, int quant);

#endif
