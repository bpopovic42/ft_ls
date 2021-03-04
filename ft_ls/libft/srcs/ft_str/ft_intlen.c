#include "libft.h"

int ft_intlen(int nbr)
{
	int    int_length;
	t_uint tmp;

	int_length = 1;
	tmp        = nbr < 0 ? (t_uint)-nbr : (t_uint)nbr;
	while (tmp)
	{
		tmp /= 10;
		int_length++;
	}
	int_length += nbr < 0 ? 0 : -1;
	return (int_length);
}
