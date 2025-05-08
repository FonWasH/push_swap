/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:27:07 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:55:17 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_clear_data(t_data *d)
{
	ft_lstclear(&d->a, free);
	ft_lstclear(&d->b, free);
	ft_lstclear(&d->c, free);
}

static void	init_args(t_args *a)
{
	a->args = NULL;
	a->free = false;
	a->tab = NULL;
	a->size = 0;
}

static t_args	ft_get_args(int ac, char **av)
{
	t_args	a;

	init_args(&a);
	if (ac == 2)
	{
		a.args = ft_split(av[1], ' ');
		if (!a.args)
			ft_error(ERROR, NULL, NULL);
		a.free = true;
		a.size = ft_mstrlen(a.args);
		if (!a.size)
			ft_error(ERROR, NULL, &a);
	}
	if (ac > 2)
	{
		a.args = av + 1;
		a.size = ac - 1;
		a.free = false;
	}
	a.tab = (int *)malloc(sizeof(int) * a.size);
	if (!a.tab)
		ft_error(ERROR, NULL, &a);
	return (a);
}

static void	ft_init_struct(t_data *d, t_args *a)
{
	t_list	*new;
	t_sdata	*data;

	d->a = NULL;
	d->b = NULL;
	d->c = NULL;
	while (a->size--)
	{
		data = (t_sdata *)malloc(sizeof(t_sdata));
		if (!data)
			ft_error(ERROR, d, a);
		data->val = a->tab[a->size];
		new = ft_lstnew(data);
		if (!new)
			ft_error(ERROR, d, a);
		ft_lstadd_front(&d->a, new);
	}
	free(a->tab);
	a->tab = NULL;
}

void	ft_check_args(int ac, char **av, t_data *d)
{
	t_args	a;
	size_t	i;
	ssize_t	tmp;

	if (DEBUG)
		ft_printf(ARG);
	a = ft_get_args(ac, av);
	i = 0;
	while (i < a.size)
	{
		tmp = ft_atol(a.args[i]);
		if (!*a.args[i] || !ft_strisdigit(a.args[i]) || ft_nisdup(a.tab, i, tmp)
			|| tmp > (ssize_t)INT_MAX || tmp < (ssize_t)INT_MIN)
			ft_error(ERROR, NULL, &a);
		a.tab[i] = (int)tmp;
		if (DEBUG)
			ft_printf("% -12d", a.tab[i]);
		i++;
	}
	if (a.free)
	{
		ft_mfree((void **)a.args, a.size);
		a.args = NULL;
	}
	ft_init_struct(d, &a);
}
