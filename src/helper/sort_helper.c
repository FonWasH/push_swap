/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:07:17 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:41:04 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_move_node_a(t_data *d, t_list *node, bool push)
{
	size_t	i;

	i = 0;
	while (i < ((t_sdata *)node->data)->top)
	{
		if (((t_sdata *)node->data)->rev)
			ft_exec_command(d, RRA);
		else
			ft_exec_command(d, RA);
		i++;
	}
	if (push)
		ft_exec_command(d, PB);
}

void	ft_move_node_b(t_data *d, t_list *node, bool push)
{
	size_t	i;

	i = 0;
	while (i < ((t_sdata *)node->data)->top)
	{
		if (((t_sdata *)node->data)->rev)
			ft_exec_command(d, RRB);
		else
			ft_exec_command(d, RB);
		i++;
	}
	if (push)
		ft_exec_command(d, PA);
}

void	ft_refresh_stack(t_list *lst)
{
	t_list	*tmp;
	size_t	size;
	size_t	mid;
	size_t	i;

	tmp = lst;
	size = ft_lstsize(lst);
	mid = size / 2;
	i = 0;
	while (tmp)
	{
		((t_sdata *)tmp->data)->index = i;
		((t_sdata *)tmp->data)->top = size - i;
		((t_sdata *)tmp->data)->rev = true;
		if (i <= mid)
		{
			((t_sdata *)tmp->data)->top = i;
			((t_sdata *)tmp->data)->rev = false;
		}
		tmp = tmp->next;
		i++;
	}
}

void	ft_calcost_stack(t_list *lst,
			t_list *(*ft_find_target)(t_list *, int), t_list *target_lst)
{
	t_list	*tmp;
	t_list	*target;
	t_sdata	*node;

	tmp = lst;
	while (tmp)
	{
		node = (t_sdata *)tmp->data;
		target = ft_find_target(target_lst, ((t_sdata *)tmp->data)->val);
		node->target = target;
		node->cost = node->top + ((t_sdata *)target->data)->top;
		tmp = tmp->next;
	}
}

t_list	*ft_get_cheapest_cost(t_list *lst)
{
	t_list	*tmp;
	t_list	*cheapest;

	tmp = lst;
	cheapest = tmp;
	while (tmp)
	{
		if (((t_sdata *)tmp->data)->cost < ((t_sdata *)cheapest->data)->cost)
			cheapest = tmp;
		if (((t_sdata *)cheapest->data)->cost == 0)
			return (cheapest);
		tmp = tmp->next;
	}
	return (cheapest);
}
