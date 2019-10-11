#include "ft_ls.h"

int		int_len(int n)
{
	int		len;

	len = 1;
	while (n / 10)
	{
		n /= 10;
		++len;
	}
	return (len);
}

int		ls_put_error(int error, char *dir_name, int returns)
{
	if (error == LSE_NODIR)
		ft_printf(LSE_NODIR_S, dir_name);
	return (returns);
}
