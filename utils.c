#include "philo.h"

int	ft_atoi_pos(char *str)
{
	long	num;
	int		ret;

	num = 0;
	if (str == NULL)
		return (-1);
	if (*str == '-')
		return (-2);
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	ret = (int) num;
	if (ret < 0)
		return (-2);
	return (ret);
}
