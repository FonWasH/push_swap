/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:02:13 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:41:16 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_sort_three(t_data *d)
{
	t_list	*max;
	t_list	*min;

	max = ft_get_max(d->a);
	min = ft_get_min(d->a);
	if (d->a == max)
		ft_exec_command(d, RA);
	else if (d->a->next == max)
		ft_exec_command(d, RRA);
	if (d->a->next == min)
		ft_exec_command(d, SA);
}

static void	ft_sort_a_to_b(t_data *d)
{
	t_list	*cheapest;

	ft_exec_command(d, PB);
	ft_exec_command(d, PB);
	while (ft_lstsize(d->a) > 3)
	{
		ft_refresh_stack(d->a);
		ft_refresh_stack(d->b);
		ft_calcost_stack(d->a, ft_get_mintarget, d->b);
		cheapest = ft_get_cheapest_cost(d->a);
		ft_move_node_b(d, ((t_sdata *)cheapest->data)->target, false);
		ft_move_node_a(d, cheapest, true);
	}
}

static void	ft_sort_b_to_a(t_data *d)
{
	t_list	*cheapest;

	while (d->b)
	{
		ft_refresh_stack(d->a);
		ft_refresh_stack(d->b);
		ft_calcost_stack(d->b, ft_get_maxtarget, d->a);
		cheapest = ft_get_cheapest_cost(d->b);
		ft_move_node_a(d, ((t_sdata *)cheapest->data)->target, false);
		ft_move_node_b(d, cheapest, true);
	}
}

static void	ft_order_stack(t_data *d)
{
	t_list	*min;
	size_t	i;

	ft_refresh_stack(d->a);
	min = ft_get_min(d->a);
	i = 0;
	while (i < ((t_sdata *)min->data)->top)
	{
		if (((t_sdata *)min->data)->rev)
			ft_exec_command(d, RRA);
		else
			ft_exec_command(d, RA);
		i++;
	}
}

void	ft_sort(t_data *d)
{
	size_t	size;

	size = ft_lstsize(d->a);
	if (size == 2)
	{
		if (((t_sdata *)d->a->data)->val > ((t_sdata *)d->a->next->data)->val)
			ft_exec_command(d, SA);
		return ;
	}
	if (size == 3)
	{
		ft_sort_three(d);
		return ;
	}
	if (size <= 100)
		ft_sort_a_to_b(d);
	else
		ft_quick_sort_a(d, size);
	ft_sort_three(d);
	ft_sort_b_to_a(d);
	ft_order_stack(d);
}
