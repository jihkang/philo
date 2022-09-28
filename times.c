#include "philo.h"

ll	get_time(void)
{
	t_val	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	await_time(ll	wait)
{
	ll	cur;
	ll	time;

	cur = get_time();
	while (42)
	{
		time = get_time();
		if (time - cur == wait)
			break ;
	}
}
