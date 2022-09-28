#include "philo.h"

void	*routine(void *data)
{
	t_data	*d;

	d = (t_data *)data;
	d->start = get_time();
	d->lastmeal = get_time();
	while (d->eat_cur != d->eat_times && d->state != DIE)
	{
		pthread_mutex_lock(d->left);
		pthread_mutex_lock(d->right);
		d->state = EAT;
		print_mutex(d);
		await_time(d->time_to_eat);
		d->lastmeal = get_time();
		d->eat_cur++;
		pthread_mutex_unlock(d->left);
		pthread_mutex_unlock(d->right);
		d->state = SLEEP;
		print_mutex(d);
		await_time(d->time_to_sleep);
		d->state = THINK;
		print_mutex(d);
	}
	return (NULL);
}

t_phd	*thread_routine(t_data *data, int num)
{
	t_phd	*phd;
	int		i;

	i = 0;
	phd = malloc(sizeof(t_phd) * num);
	if (num == 1)
		return (phd);
	while (i < num)
	{
		pthread_create(&phd[i], NULL, routine, (void*)(&data[i]));
		i++;
	}
	return (phd);
}

void	thread_monitoring(t_data *data, int num)
{
	int	i;
	int	eat_count;

	i = 0;
	eat_count = 0;
	while (42)
	{
		if (get_time() - data[i].lastmeal >= \
			data->time_to_die)
		{
			data[i].state = DIE;
			break ;
		}
		eat_count += data[i].eat_cur;
		if (i == num - 1)
		{
			if (eat_count == data[i].eat_times * num)
				break ;
			eat_count = 0;
		}
		i = (i + 1) % num;
		usleep(50);
	}
	print_die_or_done(data + i);
}

void	thread_main(t_arg *arg)
{
	int		i;
	t_phd	*phd;
	t_data	*data;
	t_mtx	*mtx;

	mtx = set_mutex(arg->num);
	data = (t_data *)malloc(sizeof(t_data) * arg->num);
	set_data(data, mtx, arg, arg->num);
	phd = thread_routine(data, arg->num);
	thread_monitoring(data, arg->num);
	while (i <= arg->num)
	{
		pthread_mutex_unlock(mtx + i);
		i++;
	}
	free(phd);
	free(mtx);
	free(data);
}

int main(int ac, char **av)
{
	t_arg	arg;
	int		res;

	res = set_argument(&arg, ac, av);
	if (res && error_handler(res))
		return (1);
	thread_main(&arg);
	return (0);
}
