#include "monitor.h"

double	get_sort_mean(t_time *time);
double	get_median(t_time *time, int offset);
int		count_outlier(t_time *time, double median);
int		cmp(const void *elem_1, const void *elem_2);

// Get the mean and sort for the future operations
double	get_sort_mean(t_time *time)
{
	double	sum = 0;
	double	mean = 0;

	for (int i = 0; i < time -> quant; ++i)
		sum += time -> time[i];

	mean  = sum / (double)(time -> quant);

	qsort((void *)time -> time, time -> quant, sizeof(double), cmp);

	return (mean);
}

int	cmp(const void *elem_1, const void *elem_2)
{
	if (*(double *)elem_1 > *(double *)elem_2)
		return (1);
	return (0);
}

double	get_median(t_time *time, int offset)
{
	int 	quant = time -> quant;
	int		half_quant = quant / 2;
	double	*tmp_offset = time -> time + offset;

	if (quant % 2)
		return (tmp_offset[half_quant]);
	return ((tmp_offset[half_quant] +
				tmp_offset[half_quant - 1]) / (double)2);
}

// Get outlier with the IQR method
// The lower half will be omitted if there is any
// because in this case it doesn't matter
int		count_outlier(t_time *time, double median)
{
	double	iqr;
	double	q_first;
	double	q_third;
	double	upper_bound;

	int		count = 0;
	int		quant = time -> quant;
	int		half_quant = quant / 2;

	time -> quant = half_quant;
	q_first = get_median(time, 0);
	if (quant % 2) // -> Odd length
		q_third = get_median(time, half_quant + 2);
	else // -> Even length
		q_third = get_median(time, half_quant + 1);
	time -> quant = quant;

	iqr = q_third - q_first;
	upper_bound = q_third + (1.5 * iqr);

	for (int i = 0; i < quant; i++)
	{
		if (time -> time[i] > upper_bound)
			count += 1;
	}
	return (count);
}
