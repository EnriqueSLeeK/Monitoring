#include "monitor.h"

size_t read_func(char *buffer, size_t size, size_t nitems, void *userdata);
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);


void	get_method(void *self, CURL *curl)
{
	t_base	*base = self;

	curl_easy_setopt(curl, CURLOPT_URL, base -> addr);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
}

void	post_method(void *self, CURL *curl)
{
	t_base	*base = self;

	curl_easy_setopt(curl, CURLOPT_URL, base -> addr);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "a");
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 1L);
	curl_easy_setopt(curl, CURLOPT_READDATA, &read_func);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
}

void	put_method(void *self, CURL *curl)
{
	t_base	*base = self;

	curl_easy_setopt(curl, CURLOPT_URL, base -> addr);
	curl_easy_setopt(curl, CURLOPT_UPLOAD_BUFFERSIZE, 1);
	curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
}

void	head_method(void *self, CURL *curl)
{
	t_base	*base = self;

	curl_easy_setopt(curl, CURLOPT_URL, base -> addr);
	curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

}

void	generic_method(void *self, CURL *curl)
{
	t_base	*base = self;
	t_http	*http = self;

	curl_easy_setopt(curl, CURLOPT_URL, base -> addr);
	curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, http -> method);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
}
