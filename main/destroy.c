#include "monitor.h"

void	destroy_obj(void **obj)
{
	t_base	*base;

	for (int i = 0; obj[i]; i++)
	{
		base = obj[i];
		base -> destroy(obj[i]);
	}
}
