/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:44:02 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/27 13:25:41 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief 		Creates a new philosofer and initializes it
/// @param id	Philosofer's id
/// @param info	Pointer to the t_info structure
/// @return		Pointer to the new philosofer
t_philo	*new_philo(int id, t_info *info)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo));
	if (!p)
		return (NULL);
	ft_bzero(p, sizeof(t_philo));
	p->id = id;
	p->info = info;
	if (info->phqty > 2 && id % 2 == 0)
		p->go = 1;
	return (p);
}

/// @brief 		Adds a new created philosofer to the list
/// @param p	Pointer to the list of philosofers
/// @param		new	Pointer to the new philosofer
void	add_philo(t_philo **p, t_philo *new)
{
	t_philo	*tmp;

	if (!*p)
	{
		*p = new;
		return ;
	}
	tmp = *p;
	while (tmp->id != new->id - 1)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = *p;
	(*p)->prev = new;
}

/// @brief		Initializes the philosofer's list
/// @param info	Pointer to the t_info structure
/// @return		Pointer to the list of philosofers
t_philo	*init_philo(t_info *info)
{
	int		i;
	t_philo	*p;
	t_philo	*new;

	p = NULL;
	new = NULL;
	i = 0;
	while (++i <= info->phqty)
	{
		new = new_philo(i, info);
		if (!new)
		{
			free_philo(p, NULL);
			free_data(info);
			return (NULL);
		}
		add_philo(&p, new);
	}
	return (p);
}

/// @brief 		Initializes the t_info structure with global info
/// @param argv	Arguments with the info to initialize
/// @return		Pointer to the t_info structure
t_info	*init_info(char **argv)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	ft_bzero(info, sizeof(t_info));
	info->phqty = ft_long_atoi(argv[PHQTY]);
	info->ttdie = ft_long_atoi(argv[TTDIE]);
	info->tteat = ft_long_atoi(argv[TTEAT]);
	info->ttslp = ft_long_atoi(argv[TTSLP]);
	if (argv[MEALQTY] != NULL)
	{
		info->eatqty = malloc(sizeof(long long));
		*info->eatqty = ft_long_atoi(argv[MEALQTY]);
		info->end = 1 - info->phqty;
	}
	if (invalid_info(info) == ERROR && free_data(info) == SUCCESS)
		return (NULL);
	ft_msec2usec(&info->ttdie);
	ft_msec2usec(&info->tteat);
	ft_msec2usec(&info->ttslp);
	if ((info->ttdie - info->tteat - info->ttslp) / 2 > 0)
		info->ttthk = (info->ttdie - info->tteat - info->ttslp) / 2;
	return (info);
}

/// @brief 		Initializes the forks
/// @param p	Pointer to the list of philosofers
/// @return		Poiter to the fork structure
t_fork	*init_fork(t_philo *p)
{
	t_fork	*f;
	int		i;

	f = malloc(sizeof(t_fork) * p->info->phqty);
	if (!f)
		return (NULL);
	ft_bzero(f, sizeof(t_fork) * p->info->phqty);
	i = 0;
	while (++i <= p->info->phqty)
	{
		f[i - 1].mtx = malloc(sizeof(pthread_mutex_t));
		if (!f[i - 1].mtx)
		{
			free_philo(p, f);
			return (NULL);
		}
		if (pthread_mutex_init(f[i - 1].mtx, NULL) != 0)
		{
			printf("Error: pthread_mutex_init\n");
			free_philo(p, f);
			return (NULL);
		}
		f[i - 1].id = i;
	}
	return (f);
}
