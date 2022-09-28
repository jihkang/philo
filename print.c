#include "philo.h"

int	error_handler(int type)
{
	if (type == 1)
	{
		printf("인자의 개수가 잘 못 되었습니다.\n");
	}
	if (type == 2)
	{
		printf("인자의 정보가 잘 못 되었습니다.\n");
	}
	return (1);
}

void	print_init_data(t_data *data, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		printf("philosopher id : %d\n", data[i].id);
		printf("philosopher left : %p\n", data[i].left);
		printf("philosopher right : %p\n", data[i].right);
		printf("philosopher prt : %p\n", data[i].prt);
		printf("philosopher state : %d\n", data[i].state);
		printf("philosopher cur eat : %d\n", data[i].eat_cur);
		printf("\n\n\n");
		i++;
	}
}

void	print_mutex(t_data *data)
{
	pthread_mutex_lock(data->prt);
	if (data->state == THINK)
		printf("%lldms %d is thinking\n", \
			get_time() - data->start, data->id);
	else if (data->state == EAT)
	{
		printf("%lldms %d has taken a fork\n", \
			get_time() - data->start, data->id);
		printf("%lldms %d has taken a fork\n", \
			get_time() - data->start, data->id);
		printf("%lldms %d is eating %d times\n", \
			get_time() - data->start, data->id, data->eat_cur);
	}
	else if (data->state == SLEEP)
		printf("%lldms %d is sleeping\n", \
			get_time() - data->start, data->id);
	pthread_mutex_unlock(data->prt);
}

void	print_die_or_done(t_data *data)
{
	pthread_mutex_lock(data->prt);
	if (data->state == DIE)
	{
		printf("%lldms %d is died\n", get_time() - data->start, data->id);
		return ;
	}
	else
	{
		printf("every done\n");
		return ;
	}
}
