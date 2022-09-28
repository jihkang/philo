#ifndef	PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define THINK	0
# define EAT	1
# define SLEEP	2
# define DIE	3
# define DONE	4

typedef pthread_mutex_t	t_mtx;
typedef pthread_t		t_phd;
typedef struct timeval	t_val;
typedef long long		ll;

typedef struct s_arg
{
	int	num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_times;
}t_arg;

typedef struct s_data
{
	t_mtx	*left;
	t_mtx	*right;
	t_mtx	*prt;
	int		id;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_times;
	int		eat_cur;
	int		state;
	ll		lastmeal;
	ll		start;
}t_data;

/*
*	time.c
*/
ll		get_time(void);
void	await_time(ll time);
/*
*	utils.c
*/
int		ft_atoi_pos(char *str);
/*
*	argue.c
*/
int		set_argument(t_arg *arg, int ac, char **av);
t_mtx	*set_mutex(int num);
void	set_data(t_data *data, t_mtx *mtx, t_arg *arg, int num);
/*
*	print.c
*/
int		error_handler(int type);
void	print_init_data(t_data *data, int num);
void	print_mutex(t_data *data);
void	print_die_or_done(t_data *data);

#endif
