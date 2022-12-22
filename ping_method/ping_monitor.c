#include "monitor.h"

static void	free_info(char **info);
static void	do_ping(int *pipe_fd, char *addr);
static int	parse_and_update(char **info, int fd_in);
static void	update_info(char **info, char *packet_size, char *dns,
		char *ip, char *icmp_seq, char *res_time);

void	*ping_monitor(void *self)
{
	t_ping	*ping = self;
	t_base	*base = self;

	int		try = 3;
	pid_t	pid;
	char	*info[5];
	int		pipe_fd[2];

	do {
		if (pipe(pipe_fd))
		{
			fprintf(stderr, "pipe opening failure\n");
			return (0);
		}

		if (fork() == 0)
			do_ping(pipe_fd, base -> addr);
		waitpid(0,0,0);

		if (parse_and_update(info, pipe_fd[0]))
		{
			base -> show(self, NULL);
			base -> write(self, NULL);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			try -= 1;
			sleep(1);
		}
		else
		{
			base -> show(self, (void *)info);
			base -> write(self, (void *)info);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			free_info(info);
			sleep(ping -> time_interval);
		}
	} while (try != 0);
	return (0);
}

static void	do_ping(int *pipe_fd, char *addr)
{
	char	*cmd[5] = {"ping", "-c", "1", addr, NULL};

	dup2(pipe_fd[1], STDERR_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	if (execvp(cmd[0], cmd))
		fprintf(stderr, "exec error!\n");
	exit(1);
}

static int	parse_and_update(char **info, int fd_in)
{
	FILE	*fd_line = fdopen(fd_in, "r");
	char	*tmp = NULL;
	size_t	buff_size;

	if (getline(&tmp, &buff_size, fd_line)) // Consume the first line
	{
		if (tmp[0] != 'P')
		{
			free(tmp);
			return (1);
		}
	}
	if (getline(&tmp, &buff_size, fd_line))
	{
		if (*tmp == '\n')
		{
			free(tmp);
			return (1);
		}
	}	// Get the right line
	nl_to_null(tmp);

	char	*token = strtok(tmp, " ");
	strtok(NULL, " "); // consume not important
	strtok(NULL, " "); // consume not important
	strtok(NULL, " "); // consume not important
	update_info(info, token, strtok(NULL, " "),
			strtok(NULL, " "), strtok(NULL, " "),
			strtok(NULL, " "));
	free(tmp);
	return (0);
}

static void	update_info(char **info, char *packet_size, char *dns,
		char *ip, char *icmp_seq, char *res_time)
{
	info[0] = strdup(packet_size);
	info[1] = strdup(dns);
	info[2] = strdup(ip);
	info[3] = strdup(icmp_seq);
	info[4] = strdup(res_time);
}

static void	free_info(char **info)
{
	for (int i = 0; i < 5; i++)
		free(info[i]);
}
