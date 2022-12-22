#ifndef HTTP
# define HTTP

typedef struct	http_struct
{
	t_base	base;
	char	*method;
	int		ret_code;
	int		time_interval;
	void	(*request_method)(void *, CURL *curl);
} t_http;

t_http	*init_http(char *name, char *protocol,
		char *addr, char *method,
		char *ret_code, char *time_interval);

void	get_method(void *self, CURL *curl);
void	post_method(void *self, CURL *curl);
void	put_method(void *self, CURL *curl);
void	head_method(void *self, CURL *curl);
void	generic_method(void *self, CURL *curl);

void	http_write(void *self, void *curl_ptr);
void	http_show(void *self, void *curl_ptr);
void	http_destroy(void *self);

void	*http_monitor(void *self);

#endif
