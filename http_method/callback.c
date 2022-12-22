#include "monitor.h"

size_t read_func(char *buffer, size_t size,
		size_t nitems, void *userdata)
{
	FILE *readhere = (FILE *)userdata;
	curl_off_t nread;

	/* copy as much data as possible into the 'ptr' buffer, but no more than
	'size' * 'nmemb' bytes! */
	size_t retcode = fread(buffer, size, nitems, readhere);

	nread = (curl_off_t)retcode;

	fprintf(stderr, "*** We read %" CURL_FORMAT_CURL_OFF_T
	  " bytes from file\n", nread);
	return retcode;
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	(void) ptr;
	(void) userdata;
	return (size * nmemb);
}
