#include "monitor.h"

void	destroy_base(t_base *self)
{
	free(self -> name);
	free(self -> protocol);
	free(self -> addr);
}
