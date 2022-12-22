#include "monitor.h"

void	*http_monitor(void *self)
{
	t_http	*http = self;
	t_base	*base = self;

	CURL	*curl;
	int		try = 3;
	int		res;

	if ((curl = curl_easy_init()) == NULL)
	{
		write(2, "curl init failure\n", 18);
		return (0);
	}
	http -> request_method(self, curl); 

	do {
		res = curl_easy_perform(curl);
		if (!res)
		{
			base -> show(self, curl);
			base -> write(self, curl);
			sleep(http -> time_interval);
		}
		else
		{
			try -= 1;
			base -> show(self, NULL);
			base -> write(self, NULL);
			sleep(1);
		}
	} while (try != 0);

	curl_easy_cleanup(curl);
	return (0);
}
