#include "philo.h"

int	set_argument(t_arg *arg, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (1);
	arg->num = ft_atoi_pos(av[1]);
	arg->time_to_die = ft_atoi_pos(av[2]);
	arg->time_to_eat = ft_atoi_pos(av[3]);
	arg->time_to_sleep = ft_atoi_pos(av[4]);
	arg->eat_times = ft_atoi_pos(av[5]);
	if (arg->num <= 0 || arg->time_to_die <= 0 || \
		arg->time_to_eat <= 0 || arg->time_to_sleep <= 0 \
		|| arg->eat_times < -1)
		return (2);
	return (0);
}

t_mtx	*set_mutex(int num)
{
	int		i;
	t_mtx	*mtx;

	i = 0;
	mtx = malloc(sizeof(t_mtx) * (num + 1));
	while (i < num)
	{
		pthread_mutex_init(mtx + i, NULL);
		i++;
	}
	return (mtx);
}

void	set_data(t_data *data, t_mtx *mtx, t_arg *arg, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		(data + i)->state = THINK;
		(data + i)->eat_cur = 0;
		(data + i)->eat_times = arg->eat_times;
		(data + i)->time_to_die = arg->time_to_die;
		(data + i)->time_to_eat = arg->time_to_eat;
		(data + i)->time_to_sleep = arg->time_to_sleep;
		(data + i)->left = mtx + i;
		(data + i)->right = mtx + ((i + 1) % num);
		(data + i)->prt = mtx + num;
		(data + i)->id = i + 1;
		(data + i)->start = get_time();
		(data + i)->lastmeal = get_time();
		i++;
	}
}
