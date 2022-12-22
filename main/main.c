#include "monitor.h"

pthread_mutex_t	write_mutex;
pthread_mutex_t	print_mutex;

static int	count_line(void);
static int	check_arg(char **argv);
static int	read_and_init(void **structure, char *file);
static int	flag(int argc, char **argv, char **alt_config);

static int	flag(int argc, char **argv, char **alt_config)
{
	int mode = check_arg(argv);

	if (mode == 1)
	{
		count_protocols();
		return (1);
	}
	else if (mode == 2)
	{
		time_analyze();
		return (1);
	}
	else if (mode == 3 && argc == 3)
	{
		if (access(argv[2], F_OK) == 0)
		{
			*alt_config = argv[2];
			return (0);
		}
		fprintf(stderr, "File doesn't exist\n");
		return (1);
	}
	else if (mode == 4)
	{
		fprintf(stdout, "./monitoring <flag> <arg when allowed>\n\
	--config-file It will take a custom configuration file as an argument\n\
	* Flags that don't take a argument:\n\
		--simplify It will printout a simplified version of the log\n\
		--analyze-time It will check if there is a outlier in the response time\n\
		--help Print out this message\n");
		return (1);
	}
	fprintf(stderr, "Bad usage: Please use the --help flag\n");
	return (1);
}

static int	check_arg(char **argv)
{
	for (int i = 1; argv[i]; i++)
	{
		if (strcmp(argv[i], "--simplify") == 0)
			return (1);
		if (strcmp(argv[i], "--analyze-time") == 0)
			return (2);
		if (strcmp(argv[i], "--config-file") == 0)
			return (3);
		if (strcmp(argv[i], "--help") == 0)
			return (4);
	}
	return (0);
}

static int	count_line(void)
{
	int		count;
	FILE	*fd;
	char	c;

	count = 0;
	fd = fopen("monitoring.db", "r");
	if (fd == 0)
		return (0);
	while ((c = fgetc(fd)) && c != EOF)
		if (c == '\n') count++;
	fclose(fd);
	return (count);
}

void	nl_to_null(char *line)
{
	for (int i = 0; line[i]; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = 0;
			break;
		}
	}
}

static int	read_and_init(void **structure, char *file)
{
	size_t	len;
	FILE	*fd;
	char	*buff;

	if (file != NULL)
		fd = fopen(file, "r");
	else
		fd = fopen("monitoring.db", "r");

	if (fd == 0)
		return (1);
	len = 0;
	buff = NULL;
	while (getline(&buff, &len, fd) != -1)
	{
		nl_to_null(buff);
		if (!check_line(buff))
		{
			*structure = init_and_parse(strtok(buff, "\t"),
										strtok(NULL, "\t"));
			structure += 1;
		}
		else
		{
			free(buff);
			fclose(fd);
			return (1);
		}
	}
	free(buff);
	fclose(fd);
	return (0);
}


int main(int argc, char *argv[])
{
	int		quant = count_line();
	char	*alternative_config = NULL;

	if (quant > 0)
	{
		if (argc > 1)
		{
			if (flag(argc, argv, &alternative_config))
				return (0);
		}

		void		*protocols[quant + 1];
		pthread_t	threads[quant];

		memset(protocols, 0, sizeof(void *) * (quant + 1));
		if (read_and_init(protocols, alternative_config) ||
			pthread_mutex_init(&write_mutex, 0) ||
			pthread_mutex_init(&print_mutex, 0) ||
			start_monitoring(protocols, threads))
		{
			write(2, "Failure at initialization\n", 26);
			destroy_obj(protocols);
			return (1);
		}
		wait_threads(threads, quant);
		pthread_mutex_destroy(&write_mutex);
		pthread_mutex_destroy(&print_mutex);
		destroy_obj(protocols);
	}
	return (0);
}
