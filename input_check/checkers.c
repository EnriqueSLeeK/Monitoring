#include "monitor.h"
#include <regex.h>

int	check_address(char *segment)
{
	int		check_match;

	/* Checking in order
	 * - ip
	 * - url with protocol
	 * - url without protocol
	 */
	check_match = regex_match(segment, "^[1-9]{1,3}\\.[1-9]{1,3}\\.[1-9]{1,3}\\.[1-9]{1,3}$") +
	regex_match(segment, "^[A-Za-z]+:\\/\\/[A-Za-z0-9\\-_]+\\.[A-Za-z0-9\\-_:%&;\\?\\#\\/.=]+$") +
	regex_match(segment, "^[A-Za-z0-9\\-_]+\\.[A-Za-z0-9\\-_:%&;\\?\\#\\/.=]+$");
	if (check_match <= REG_NOMATCH * 2)
		return (0);
	return (1);
}

int	regex_match(char *segment, char *pattern)
{
	int		ret;
	regex_t	reg;

	if (segment == 0 || pattern == 0)
		return (1);
	if (regcomp(&reg, pattern, REG_EXTENDED))
	{
		fprintf(stderr, "Failure %s init\n", "reg");
		return (1);
	}
	ret = regexec(&reg, segment, 0, NULL, 0);
	regfree(&reg);
	return (ret);
}
